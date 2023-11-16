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
};

#endif // !VERT_POS_H