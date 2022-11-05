#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    int triangleAmount, float radius,
    glm::vec3 color)
{

    float x = leftBottomCorner[0];

    float y = leftBottomCorner[1];

    std::vector<VertexFormat> vertices;

    float twicePi = 2.0f * M_PI;
    for (int i = 0; i <= triangleAmount; i++)
    {
        vertices.push_back(VertexFormat(glm::vec3(x + (radius * cos(i * twicePi / triangleAmount)),
                               y + (radius * sin(i * twicePi / triangleAmount)), 0), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;
    circle->SetDrawMode(GL_TRIANGLE_FAN);
    for (int i = 0; i <= triangleAmount; i++)
    {
        indices.push_back(i);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateTriangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    glm::vec3 point1,
    glm::vec3 point2,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    // float x = leftBottomCorner[0];

    // float y = leftBottomCorner[1];

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color),
        VertexFormat(corner + point1, color),
        VertexFormat(corner + point2, color),
        // VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    // float radius = 50;
    // float twicePi = 2.0f * M_PI;
    // for (int i = 0; i <= triangleAmount; i++)
    // {
    //     vertices.push_back(VertexFormat(glm::vec3(x + (radius * cos(i * twicePi / triangleAmount)),
    //                            y + (radius * sin(i * twicePi / triangleAmount)), 0), color));
    // }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2};
    circle->SetDrawMode(GL_TRIANGLES);
    // for (int i = 0; i <= triangleAmount; i++)
    // {
    //     indices.push_back(i);
    // }
    circle->InitFromData(vertices, indices);
    return circle;
}