#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

//#ifdef __linux
//#define GL_GLEXT_PROTOTYPES 1
//#endif

#include <QOpenGLFunctions_4_5_Core>
#include <string>
#include <QDebug>
#include <GL/glu.h>

#include "mathgl.h"


//Klasa zarzadzajaca programem shadera
// .... do dalszej rozbudowy ....
class GLSLProgram :  protected QOpenGLFunctions_4_5_Core
{
    GLuint handle;
    bool checkShaderStatus(GLuint);
    bool checkProgramStatus(GLuint);

public:
    GLSLProgram();
    //~GLSLProgram();
    bool compileShaderFromFile(const char* filename, GLenum type);
    bool compileShaderFromString(const std::string& source, GLenum type);
    bool link();
    void use();
    //void bindAttribLocation(GLuint location, const char* name);
    void setUniform(const char* name, int v);
    //void setUniform(const char* name, float v);
    void setUniform(const char* name, vec2 v);
    void setUniform(const char* name, vec3 v);
    void setUniform(const char* name, mat4 mat);
};

#endif // GLSLPROGRAM_H
