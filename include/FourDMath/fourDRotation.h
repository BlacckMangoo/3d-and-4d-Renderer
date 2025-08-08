#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>
// 4D rotation matrices for the 6 possible rotation planes
class Rotation4D {
public:
    // Create 4x4 rotation matrix for XY plane (rotate around Z-W axis)
    static glm::mat4 rotateXY(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    // Create 4x4 rotation matrix for XZ plane (rotate around Y-W axis)
    static glm::mat4 rotateXZ(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            c, 0, -s, 0,
            0, 1, 0, 0,
            s, 0, c, 0,
            0, 0, 0, 1
        );
    }

    // Create 4x4 rotation matrix for XW plane (rotate around Y-Z axis)
    static glm::mat4 rotateXW(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            c, 0, 0, -s,
            0, 1, 0, 0,
            0, 0, 1, 0,
            s, 0, 0, c
        );
    }

    // Create 4x4 rotation matrix for YZ plane (rotate around X-W axis)
    static glm::mat4 rotateYZ(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1
        );
    }

    // Create 4x4 rotation matrix for YW plane (rotate around X-Z axis)
    static glm::mat4 rotateYW(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            1, 0, 0, 0,
            0, c, 0, -s,
            0, 0, 1, 0,
            0, s, 0, c
        );
    }

    // Create 4x4 rotation matrix for ZW plane (rotate around X-Y axis)
    static glm::mat4 rotateZW(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, c, -s,
            0, 0, s, c
        );
    }

    // Double rotation: combine two rotations
    static glm::mat4 doubleRotation(float angleXY, float angleZW) {
        return rotateZW(angleZW) * rotateXY(angleXY);
    }

    // More complex double rotation combining different planes
    static glm::mat4 complexDoubleRotation(float angle1, float angle2,
        int plane1 = 0, int plane2 = 5) {
        glm::mat4 rot1, rot2;

        // Select first rotation plane
        switch (plane1) {
        case 0: rot1 = rotateXY(angle1); break;
        case 1: rot1 = rotateXZ(angle1); break;
        case 2: rot1 = rotateXW(angle1); break;
        case 3: rot1 = rotateYZ(angle1); break;
        case 4: rot1 = rotateYW(angle1); break;
        case 5: rot1 = rotateZW(angle1); break;
        default: rot1 = glm::mat4(1.0f); break;
        }

        // Select second rotation plane
        switch (plane2) {
        case 0: rot2 = rotateXY(angle2); break;
        case 1: rot2 = rotateXZ(angle2); break;
        case 2: rot2 = rotateXW(angle2); break;
        case 3: rot2 = rotateYZ(angle2); break;
        case 4: rot2 = rotateYW(angle2); break;
        case 5: rot2 = rotateZW(angle2); break;
        default: rot2 = glm::mat4(1.0f); break;
        }

        return rot2 * rot1;
    }
};



