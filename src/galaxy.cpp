#include "../include/Renderer/galaxy.h"
#include<random>
#include "Renderer/shaderList.h"

Galaxy::Galaxy(int particleCount): particleCount(particleCount)
{
    galaxyRadius = 100.0f;
    particles.reserve(particleCount);  // Reserve space instead of resize

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist01(0.0f, 1.0f);
    std::uniform_real_distribution<float> distMass(1.0f, 10.0f);

    for (size_t i = 0; i < particleCount; i++)
    {
        // Spherical coordinates for uniform distribution in a sphere
        float u = dist01(rng);
        float v = dist01(rng);
        float theta = u * 2.0f * glm::pi<float>();
        float phi = acos(2.0f * v - 1.0f);
        float r = cbrt(dist01(rng)) * galaxyRadius;

        glm::vec3 pos(
            r * sin(phi) * cos(theta),
            r * sin(phi) * sin(theta),
            r * cos(phi)
        );

        Particle p;
        p.position = pos;
        p.velocity = glm::vec3(0.0f);
        p.acceleration = glm::vec3(0.0f);
        p.mass = distMass(rng);

        particles.push_back(p);  // Now this creates exactly particleCount particles
    }

    // OpenGL setup
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // Allocate buffer for the actual number of particles
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), particles.data(), GL_DYNAMIC_DRAW);
    // Position attribute - assumes Particle::position is the first member
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Galaxy::Draw(Camera& camera)
{
    GlobalShaders::galaxyShader->Use();
    GlobalShaders::galaxyShader->SetMatrix4("view", camera.GetViewMatrix());
    GlobalShaders::galaxyShader->SetMatrix4("projection", camera.GetProjectionMatrix());
    GlobalShaders::galaxyShader->SetVector3f("uColor", 1.0f, 1.0f, 1.0f);

    // Update the entire particle buffer with current data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * sizeof(Particle), particles.data());

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(particles.size()));
}

Galaxy::~Galaxy() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Galaxy::Update(float dt)
{
    // Using a static RNG so we don't reseed every frame
    static std::mt19937 rng(std::random_device{}());
    // Increase the offset for more visible movement
    float maxOffset = 45.0f;
    std::uniform_real_distribution<float> offsetDist(-maxOffset, maxOffset);

    for (auto& particle : particles)
    {
        glm::vec3 randomOffset(
            offsetDist(rng),
            offsetDist(rng),
            offsetDist(rng)
        );

        randomOffset *= dt;
        particle.position += randomOffset;
    }
}