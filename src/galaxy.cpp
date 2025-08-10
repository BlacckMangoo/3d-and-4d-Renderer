#include "../include/Renderer/galaxy.h"
#include<random>
#include "Renderer/shaderList.h"
#include "barnesHutOctree.h"

Galaxy::Galaxy(int particleCount): particleCount(particleCount)
{
    galaxyRadius = 1000.0f;
    particles.reserve(particleCount);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist01(0.0f, 1.0f);
    std::uniform_real_distribution<float> distMass(0.1f, 2.0f);
    std::uniform_real_distribution<float> angleRange(0.0f, 2.0f * 3.14159265359f);


    Particle blackHole = Particle();
    blackHole.mass = 10.0f;
    blackHole.position = glm::vec3(0.0f, 0.0f, 0.0f);
    blackHole.velocity = glm::vec3(0.0f);
    blackHole.acceleration = glm::vec3(0.0f);
    particles.push_back(blackHole);

    const float G = 1.0f; // Gravitational constant
    const float diskThickness = galaxyRadius * 0.1f; // Thin disk

    // Create particles in a galaxy disk distribution
    for (size_t i = 1; i < particleCount; i++)
    {
        Particle p;
        p.mass = distMass(rng);

        // Generate position in disk using exponential distribution for realistic galaxy profile
        float r = galaxyRadius * sqrt(dist01(rng)); // Square root gives more realistic radial distribution
        float theta = angleRange(rng); // Random angle around disk
        float z = (dist01(rng) - 0.5f) * diskThickness; // Small vertical spread

        p.position = glm::vec3(
            r * cos(theta),
            z, // y is up
            r * sin(theta)
        );

        // Calculate orbital velocity for stable orbit
        float distanceFromCenter = glm::length(glm::vec3(p.position.x, 0.0f, p.position.z)); // Distance in disk plane

        if (distanceFromCenter > 0.1f) {
            // Keplerian velocity: v = sqrt(GM/r)
            float orbitalSpeed = sqrt(G * blackHole.mass / distanceFromCenter);

            // Add velocity dispersion and rotation curve flattening for realism
            orbitalSpeed *= (0.7f + 0.5f * dist01(rng)); // Random factor between 0.7 and 1.2

            // Velocity direction tangent to orbit in the disk
            glm::vec3 radialDir = glm::normalize(glm::vec3(p.position.x, 0.0f, p.position.z));
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 tangentialDir = glm::cross(up, radialDir); // Counterclockwise rotation

            p.velocity = tangentialDir * orbitalSpeed;

            // Add small random velocity components for realism
            p.velocity += glm::vec3(
                (dist01(rng) - 0.5f) * orbitalSpeed * 0.1f, // Radial velocity dispersion
                (dist01(rng) - 0.5f) * orbitalSpeed * 0.05f, // Vertical velocity dispersion
                (dist01(rng) - 0.5f) * orbitalSpeed * 0.1f  // Azimuthal velocity dispersion
            );
        } else {
            p.velocity = glm::vec3(0.0f);
        }

        p.acceleration = glm::vec3(0.0f);
        particles.push_back(p);
    }

    // OpenGL setup
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), particles.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Galaxy::Draw(Camera& camera)
{
    GlobalShaders::galaxyShader->Use();
    GlobalShaders::galaxyShader->SetMatrix4("view", camera.GetViewMatrix());
    GlobalShaders::galaxyShader->SetMatrix4("projection", camera.GetProjectionMatrix());

    glBindVertexArray(vao);

    // Draw black hole in different color
    GlobalShaders::galaxyShader->SetVector3f("uColor", 1.0f, 0.2f, 0.2f); // Red for black hole
    glDrawArrays(GL_POINTS, 0, 1);

    // Draw galaxy particles
    GlobalShaders::galaxyShader->SetVector3f("uColor", 0.8f, 0.9f, 1.0f); // Blue-white for stars
    glDrawArrays(GL_POINTS, 1, static_cast<GLsizei>(particles.size() - 1));
}

Galaxy::~Galaxy() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Galaxy::Update(float dt)
{
    // Skip if no particles
    if (particles.size() <= 1) return;

    // Build list of pointers for Barnes–Hut
    std::vector<Particle*> particlePtrs;
    particlePtrs.reserve(particles.size());
    for (auto& p : particles) {
        particlePtrs.push_back(&p);
    }

    // Build Barnes–Hut tree (includes black hole for force calc)
    BarnesHutOctree octree(0.5f);
    octree.BuildTree(particlePtrs);

    // Leapfrog integration variables
    Particle tempParticle;

    // First: half-step velocity update
    for (size_t i = 1; i < particles.size(); ++i) // skip black hole at index 0
    {
        Particle& p = particles[i];
        tempParticle.mass = p.mass;
        tempParticle.position = p.position;

        glm::vec3 force(0.0f);
        octree.calculateForces(octree.getRoot(), &tempParticle, force);

        if (p.mass > 0.0f)
            p.velocity += (force / p.mass) * (0.5f * dt);
    }

    // Second: full-step position update
    for (size_t i = 1; i < particles.size(); ++i)
    {
        Particle& p = particles[i];
        p.position += p.velocity * dt;

        // Boundary clamp + damped reflection
        float maxDistance = galaxyRadius * 5.0f; // Larger boundary
        float dist = glm::length(p.position);
        if (dist > maxDistance) {
            glm::vec3 dir = glm::normalize(p.position);
            p.position = dir * maxDistance;
            float vDot = glm::dot(p.velocity, dir);
            if (vDot > 0)
                p.velocity -= 2.0f * vDot * dir * 0.5f;
        }
    }

    // Rebuild tree for second half-step velocity update
    particlePtrs.clear();
    for (auto& p : particles) {
        particlePtrs.push_back(&p);
    }
    octree.BuildTree(particlePtrs);

    // Third: second half-step velocity update
    for (size_t i = 1; i < particles.size(); ++i)
    {
        Particle& p = particles[i];
        tempParticle.mass = p.mass;
        tempParticle.position = p.position;

        glm::vec3 force(0.0f);
        octree.calculateForces(octree.getRoot(), &tempParticle, force);

        if (p.mass > 0.0f)
            p.velocity += (force / p.mass) * (0.5f * dt);

        // Light damping to prevent numerical instabilities
        p.velocity *= 0.9995f; // Much less damping to preserve orbital motion

        // Update acceleration for debug
        p.acceleration = (p.mass > 0.0f) ? (force / p.mass) : glm::vec3(0.0f);
    }

    // Upload full particle data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * sizeof(Particle), particles.data());
}