#include "../include/barnesHutOctree.h"

// Constructor and destructor
BarnesHutOctree::BarnesHutOctree(float theta) : theta(theta), root(nullptr) {}

BarnesHutOctree::~BarnesHutOctree() {
    if (root) {
        deleteNode(root);
    }
}

void BarnesHutOctree::BuildTree(std::vector<Particle*>& particles)
{

    if (root) {
        deleteNode(root);
        root = nullptr;
    }

    if (particles.empty()) return;

    // Find bounds
    glm::vec3 min(FLT_MAX), max(-FLT_MAX);
    for (auto& p : particles)
    {
        min = glm::min(min, p->position);
        max = glm::max(max, p->position);
    }

    glm::vec3 centre = (min + max) / 2.0f;
    float halfSize = glm::length(max - min) / 2.0f;

    // Add some padding to ensure all particles fit
    halfSize *= 1.1f;

    root = new BarnesHutTreeNode();
    root->centre = centre;
    root->halfSize = halfSize;
    root->mass = 0;
    root->com = glm::vec3(0);

    // Initialize children to nullptr
    for (int i = 0; i < 8; i++) {
        root->children[i] = nullptr;
    }

    for (auto& p : particles)
    {
        InsertParticle(root, p);
    }
}

void BarnesHutOctree::InsertParticle(BarnesHutTreeNode* node, Particle* particle)
{
    // Update center of mass BEFORE adding mass
    if (node->mass > 0) {
        node->com = (node->com * node->mass + particle->position * particle->mass) / (node->mass + particle->mass);
    } else {
        node->com = particle->position;
    }
    node->mass += particle->mass;

    // If leaf and empty
    if (!node->children[0] && node->particles.empty())
    {
        node->particles.push_back(particle);
        return;
    }

    // If leaf with one particle, subdivide
    if (!node->children[0] && node->particles.size() == 1)
    {
        Particle* existingParticle = node->particles[0];
        node->particles.clear();
        subdivide(node);

        // Re-insert existing particle
        int existingIndex = getChildIndex(node, existingParticle->position);
        InsertParticle(node->children[existingIndex], existingParticle);

        // Insert new particle
        int newIndex = getChildIndex(node, particle->position);
        InsertParticle(node->children[newIndex], particle);
        return;
    }

    // Else insert into the correct child
    int index = getChildIndex(node, particle->position);
    InsertParticle(node->children[index], particle);
}

void BarnesHutOctree::subdivide(BarnesHutTreeNode* node)
{
    float hs = node->halfSize / 2.0f;
    glm::vec3 centre = node->centre;

    // Create 8 children
    for (int i = 0; i < 8; i++) {
        node->children[i] = new BarnesHutTreeNode();
        node->children[i]->halfSize = hs;
        node->children[i]->mass = 0;
        node->children[i]->com = glm::vec3(0);

        // Initialize children's children to nullptr
        for (int j = 0; j < 8; j++) {
            node->children[i]->children[j] = nullptr;
        }
    }

    // Set positions for each octant
    //top left back
    node->children[0]->centre = centre + glm::vec3(-hs, -hs, -hs);
    //top right back
    node->children[1]->centre = centre + glm::vec3(hs, -hs, -hs);
    //bottom left back
    node->children[2]->centre = centre + glm::vec3(-hs, hs, -hs);
    //bottom right back
    node->children[3]->centre = centre + glm::vec3(hs, hs, -hs);
    //top left front
    node->children[4]->centre = centre + glm::vec3(-hs, -hs, hs);
    //top right front
    node->children[5]->centre = centre + glm::vec3(hs, -hs, hs);
    //bottom left front
    node->children[6]->centre = centre + glm::vec3(-hs, hs, hs);
    //bottom right front
    node->children[7]->centre = centre + glm::vec3(hs, hs, hs);
}

int BarnesHutOctree::getChildIndex(BarnesHutTreeNode* node, glm::vec3 pos)
{
    bool left = pos.x < node->centre.x;
    bool top = pos.y < node->centre.y;
    bool back = pos.z < node->centre.z;

    if (left && top && back) return 0;      // top left back
    if (!left && top && back) return 1;     // top right back
    if (left && !top && back) return 2;     // bottom left back
    if (!left && !top && back) return 3;    // bottom right back
    if (left && top && !back) return 4;     // top left front
    if (!left && top && !back) return 5;    // top right front
    if (left && !top && !back) return 6;    // bottom left front
    if (!left && !top && !back) return 7;   // bottom right front

    // Should never reach here, but return 0 as fallback
    return 0;
}

// Calculate gravitational forces using Barnes-Hut approximation
void BarnesHutOctree::calculateForces(BarnesHutTreeNode* node, Particle* particle, glm::vec3& force)
{
    if (!node || node->mass == 0) return;

    glm::vec3 r = node->com - particle->position;
    float distance = glm::length(r);

    // Avoid self-interaction
    if (distance < 1e-6f) return;

    // Check if we can use this node's approximation
    // If it's a leaf node OR if it's far enough away
    bool isLeaf = !node->children[0] || !node->particles.empty();
    bool farEnough = (node->halfSize * 2.0f / distance) < theta;

    if (isLeaf || farEnough) {
        // Use this node for force calculation
        const float G = 1.0f; // Gravitational constant (adjust for your simulation scale)
        const float softening = 0.01f; // Softening parameter

        float forceMagnitude = G * particle->mass * node->mass /
                              (distance * distance + softening * softening);

        if (distance > 0) {
            force += (r / distance) * forceMagnitude;
        }
    }
    else {
        // Recursively calculate forces from children
        for (int i = 0; i < 8; i++) {
            if (node->children[i]) {
                calculateForces(node->children[i], particle, force);
            }
        }
    }
}

// Clean up memory
void BarnesHutOctree::deleteNode(BarnesHutTreeNode* node)
{
    if (!node) return;

    for (int i = 0; i < 8; i++) {
        if (node->children[i]) {
            deleteNode(node->children[i]);
        }
    }
    delete node;
}

// Get the root node
BarnesHutTreeNode* BarnesHutOctree::getRoot()
{
    return root;
}