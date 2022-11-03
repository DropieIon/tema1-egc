#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create circle

    Mesh *CreateCircle(const std::string &name,
                       glm::vec3 leftBottomCorner,
                       float length,
                       glm::vec3 color,
                       bool fill);

    
    // void cc(int x, int y, int k, int r, int h);
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}
