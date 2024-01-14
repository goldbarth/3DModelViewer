// Added by me to store texture coordinates

#ifndef TEX_COORDS_H
#define TEX_COORDS_H

#include <glad/glad.h>


class TexCoords
{
public:
    TexCoords(const GLfloat u, const GLfloat v)
        : uCoord(u), vCoord(v) {}

    GLfloat uCoord;
    GLfloat vCoord;
};
    
#endif // !TEX_COORDS_H
