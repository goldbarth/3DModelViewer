// Added by me to store texture coordinates

#ifndef VERTEX_UVS_H
#define VERTEX_UVS_H

#include <glad/glad.h>


class VertexUVs
{
public:
    VertexUVs(const GLfloat u, const GLfloat v)
        : uCoord(u), vCoord(v) {}

    GLfloat uCoord;
    GLfloat vCoord;
};
    
#endif // !VERTEX_UVS_H
