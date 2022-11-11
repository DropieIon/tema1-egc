#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    Mesh* CreateRectangle(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        float width,
        float length,
        glm::vec3 color,
        bool fill = false);
    Mesh *CreateCircle(const std::string &name, glm::vec3 leftBottomCorner, int triangleAmount, float radius, glm::vec3 color);
    Mesh* CreateTriangle(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        glm::vec3 point1,
        glm::vec3 point2,
        glm::vec3 color);
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}
