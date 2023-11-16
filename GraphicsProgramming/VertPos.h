// Added by me to store vertex positions

#ifndef VERT_POS_H
#define VERT_POS_H

#include <glad/glad.h>

class VertPos
{
public:
    VertPos(const GLfloat xPos, const GLfloat yPos, const GLfloat zPos)
        : x(xPos), y(yPos), z(zPos) {}

    GLfloat x;
    GLfloat y;
    GLfloat z;

    // VertPos getters/setters
    GLfloat GetXPos() { return x; }
    GLfloat GetYPos() { return y; }
    GLfloat GetZPos() { return z; }

    void SetXPos(const GLfloat xPos) { x = xPos; }
    void SetYPos(const GLfloat yPos) { y = yPos; }
    void SetZPos(const GLfloat zPos) { z = zPos; }
};

#endif // !VERT_POS_H