#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

class Color
{
public:
    Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif // !COLOR_H
