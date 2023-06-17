#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QOpenGLFunctions_4_5_Core>
#include <string>
#include <QDebug>
#include <GL/glu.h>

#include "mathgl.h"

class Texture2D : protected QOpenGLFunctions_4_5_Core
{
    GLuint handle;
public:
    Texture2D();

    bool loadFromFile(const char* path);

    void bind(int tex_unit = 0);
    void unbind();
};

#endif // TEXTURE2D_H
