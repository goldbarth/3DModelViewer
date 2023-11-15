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

    // Color getters/setters
    GLfloat GetRed() const { return red; }
    GLfloat GetGreen() const { return green; }
    GLfloat GetBlue() const { return blue; }
    GLfloat GetAlpha() const { return alpha; }

    void SetRed(const GLfloat r) { red = r; }
    void SetGreen(const GLfloat g) { green = g; }
    void SetBlue(const GLfloat b) { blue = b; }
    void SetAlpha(const GLfloat a) { alpha = a; }
};

#endif // !COLOR_H
