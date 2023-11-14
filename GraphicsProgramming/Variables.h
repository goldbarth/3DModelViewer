#ifndef VARIABLES_H
#define VARIABLES_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Color.h"

struct Vertex
{
    glm::vec3 position;
    Color color;

    Vertex(const glm::vec3& pos, const Color& col)
        : position(pos), color(col) {}
};

#endif //!VARIABLES_H
