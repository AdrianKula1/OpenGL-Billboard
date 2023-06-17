#ifndef MATHGL_H
#define MATHGL_H
#include <QDebug>

#include <math.h>
#include <GL/glu.h>

inline void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR) { qDebug() << "ERROR in: " << mess << (const char*)gluErrorString(err); }
}


struct vec2 { float x,y; };
struct vec3 { float x,y,z; };
struct vec4 { float x,y,z,w; };

struct mat4 { float m[16]; };

inline float deg2rad(float deg)
{
    return deg*M_PI/180.0f;
}

inline float len(const vec3& v)
{
    return std::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

inline vec3 normal(const vec3& v)
{
    float l = len(v);
    return vec3{v.x/l, v.y/l, v.z/l};
}

inline vec3& normalize(vec3& v)
{
    float l = len(v);
    v.x = v.x/l;
    v.y = v.y/l;
    v.z = v.z/l;
    return v;
}

inline float dot(const vec3& v1, const vec3& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
    vec3 ret;
    ret.x = v1.y*v2.z - v1.z*v2.y;
    ret.y = -v1.x*v2.z + v1.z*v2.x;
    ret.z = v1.x*v2.y - v1.y*v2.x;
    return ret;
}

inline vec3 operator*(const vec3& a, float f)
{
    return vec3{a.x*f, a.y*f, a.z*f};
}

inline vec3 operator+(const vec3& a, const vec3& b)
{
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline vec3 operator-(vec3 v1, vec3 v2)
{
    return vec3{v1.x-v2.x, v1.y-v2.y, v1.z-v2.z};
}

inline vec3& operator+=(vec3& a, const vec3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline vec3 calcNormal(const vec3& v1, const vec3& v2, const vec3& v3)
{
    vec3 v12 = v2 - v1;
    vec3 v13 = v3 - v1;
    return normal(cross(v12, v13));
}

inline mat4 identity()
{
    mat4 m;
    memset(m.m, 0, 16*4);
    m.m[0]=m.m[5]=m.m[10]=m.m[15]=1.0f;
    return m;
}

mat4 translation_mat(float x, float y, float z);

mat4 rotation_mat(float angle, float x, float y, float z);

mat4 scale_mat(float x, float y, float z);

inline mat4 inversed(const mat4& mat){
    mat4 mret = identity();
    //...

    return mret;
}

mat4 transposed(const mat4& m);

mat4 mul(const mat4& m1, const mat4& m2);

inline mat4 operator*(const mat4& m1, const mat4& m2)
{
    return mul(m1, m2);
}

inline vec3 mul(const mat4& m, const vec3& v)
{
    vec3 vret;
    vret.x = v.x*m.m[0] + v.y*m.m[4] + v.z*m.m[8]  + m.m[12];
    vret.y = v.x*m.m[1] + v.y*m.m[5] + v.z*m.m[9]  + m.m[13];
    vret.z = v.x*m.m[2] + v.y*m.m[6] + v.z*m.m[10] + m.m[14];
    return vret;
}

inline vec4 mul(const mat4& m1, const vec4& v)
{
    vec4 vret;
    //...
    return vret;
}

mat4 perspective(float fovy, float aspect, float znear, float zfar);
mat4 ortho(float left, float right, float bottom, float  top, float F, float far);


class Frame
{
public:
    Frame();
    vec3 up;//camera right
    //to jest wektor kamery wskazujący w górę
    vec3 forward;
    vec3 pos;

    virtual vec3 s();//camera up
    virtual mat4 matrix(bool rotationOnly=false);
};


inline void rotateFrame(Frame& frame, float angle, float x, float y, float z)
{
    mat4 mr = rotation_mat(angle, x,y,z);
    frame.up = mul(mr, frame.up);
    frame.forward = mul(mr, frame.forward);

}

class Camera : public Frame
{
public:
    virtual vec3 s()
    {
        return cross(forward, up);
    }

    virtual mat4 matrix(bool rotationOnly = false);
};

#endif // MATHGL_H
