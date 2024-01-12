#ifndef NORMALS_H
#define NORMALS_H

#include <glad/glad.h>

class Normals
{
public:
    Normals(const GLfloat x, const GLfloat y, const GLfloat z)
        : xCoord(x), yCoord(y), zCoord(z) {}
    
    GLfloat xCoord;
    GLfloat yCoord;
    GLfloat zCoord;
};


#endif // !NORMALS_H