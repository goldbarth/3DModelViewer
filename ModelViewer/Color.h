// Added by me to store color values

#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

class Color
{
public:
    Color(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
    
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif // !COLOR_H
