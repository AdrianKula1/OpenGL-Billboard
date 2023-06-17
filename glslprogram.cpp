#include "glslprogram.h"
#include <QDebug>
#include <GL/glu.h>
#include <QFile>

GLSLProgram::GLSLProgram()
{
    initializeOpenGLFunctions();
    handle = glCreateProgram();
}

bool GLSLProgram::compileShaderFromFile(const char *filename, GLenum type)
{
    QFile file(filename);
    if (file.open(QFile::ReadOnly))
    {
        std::string shader_code = file.readAll().toStdString();
        return compileShaderFromString(shader_code, type);
    }
    else
    {
        qDebug() << "WARNING: GLSLProgram::compileShaderFromFile() - unable to open shader file!";
    }
    return false;
}

bool GLSLProgram::compileShaderFromString(const std::string &source, GLenum type)
{
    GLuint sh = glCreateShader(type);
    GLchar* srcs[] = {(GLchar*)source.c_str()};
    glShaderSource(sh, 1, srcs, NULL);
    glCompileShader(sh);
    if( checkShaderStatus(sh) )
    {
        glAttachShader(handle, sh);
        glDeleteShader(sh);
        return true;
    }
    return false;
}

bool GLSLProgram::link()
{
    glLinkProgram(handle);
    return checkProgramStatus(handle);
}

void GLSLProgram::use()
{
    glUseProgram(handle);
    PRINT_GL_ERRORS("GLSLProgram::use(): ");
}

void GLSLProgram::setUniform(const char *name, int v)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
        glUniform1i(loc, v);
}

void GLSLProgram::setUniform(const char *name, vec2 v)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
        glUniform2fv(loc, 1, &v.x);
}

void GLSLProgram::setUniform(const char* name, vec3 v)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
        glUniform3fv(loc, 1, &v.x);
    // else PRINT SOME ERROR
}

void GLSLProgram::setUniform(const char *name, mat4 mat)
{
    GLint loc = glGetUniformLocation(handle, name);
    if(loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat.m);
    // else PRINT SOME ERROR
}

bool GLSLProgram::checkShaderStatus(GLuint shader)
{
  GLint stat;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
  if(stat == GL_FALSE)
  {
    GLchar infoLog[10240];
    glGetShaderInfoLog(shader, 10240, NULL, infoLog);
    qDebug() << "Shader ERROR: " << infoLog;
    return false;
  }
  return true;
}

bool GLSLProgram::checkProgramStatus(GLuint program)
{
  GLint stat;
  glGetProgramiv(program, GL_LINK_STATUS, &stat);
  if(stat == GL_FALSE)
  {
    GLchar infoLog[10240];
    glGetProgramInfoLog(program, 10240, NULL, infoLog);
    qDebug() << "Program ERROR: " << infoLog;
    return false;
  }
  else
  {
    qDebug() << "Program LINKED";
  }
  return true;
}
