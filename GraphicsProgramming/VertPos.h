// Added by me to store vertex positions

#ifndef VERT_POS_H
#define VERT_POS_H

#include <glad/glad.h>

class VertPos
{
public:
    VertPos(const GLfloat x, const GLfloat y, const GLfloat z)
        : xPos(x), yPos(y), zPos(z) {}

    GLfloat xPos;
    GLfloat yPos;
    GLfloat zPos;

    // VertPos getters/setters
    GLfloat GetXPos() const { return xPos; }
    GLfloat GetYPos() const { return yPos; }
    GLfloat GetZPos() const { return zPos; }

    void SetXPos(const GLfloat x) { xPos = x; }
    void SetYPos(const GLfloat y) { yPos = y; }
    void SetZPos(const GLfloat z) { zPos = z; }
};

#endif // !VERT_POS_H