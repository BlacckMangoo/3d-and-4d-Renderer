#pragma once
#include <vector>
#include <Renderer/galaxy.h>
#include <cfloat>

struct BarnesHutTreeNode
{
    glm::vec3 centre = {0,0,0};
    float halfSize = 0;
    float mass = 0;
    glm::vec3 com = {0,0,0};
    BarnesHutTreeNode* children[8];
    std::vector<Particle*> particles;

    // Constructor
    BarnesHutTreeNode() {
        for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
        }
    }
};

class BarnesHutOctree
{
private:
    BarnesHutTreeNode* root;
    float theta; // Approximation parameter (typically 0.5)

public:
    // Constructor and destructor
    BarnesHutOctree(float theta = 0.5f);
    ~BarnesHutOctree();

    // Tree building methods
    void BuildTree(std::vector<Particle*>& particles);
    void InsertParticle(BarnesHutTreeNode* node, Particle* particle);
    void subdivide(BarnesHutTreeNode* node);
    int getChildIndex(BarnesHutTreeNode* node, glm::vec3 pos);

    // Force calculation
    void calculateForces(BarnesHutTreeNode* node, Particle* particle, glm::vec3& force);

    // Utility methods
    void deleteNode(BarnesHutTreeNode* node);
    BarnesHutTreeNode* getRoot();
};