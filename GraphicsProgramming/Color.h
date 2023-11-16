// Added by me to store color values

#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

class Color
{
public:
    Color(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a = 1.0f)
        : red(r), green(g), blue(b), alpha(a) {}

    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
};

#endif // !COLOR_H
