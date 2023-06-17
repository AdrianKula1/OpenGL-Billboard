#include "mathgl.h"



mat4 mul(const mat4 &m1, const mat4 &m2)
{
    mat4 mret;
    mret.m[0] = m1.m[0]*m2.m[0] + m1.m[4]*m2.m[1] + m1.m[8]*m2.m[2]  + m1.m[12]*m2.m[3];
    mret.m[1] = m1.m[1]*m2.m[0] + m1.m[5]*m2.m[1] + m1.m[9]*m2.m[2]  + m1.m[13]*m2.m[3];
    mret.m[2] = m1.m[2]*m2.m[0] + m1.m[6]*m2.m[1] + m1.m[10]*m2.m[2] + m1.m[14]*m2.m[3];
    mret.m[3] = m1.m[3]*m2.m[0] + m1.m[7]*m2.m[1] + m1.m[11]*m2.m[2] + m1.m[15]*m2.m[3];

    mret.m[4] = m1.m[0]*m2.m[4] + m1.m[4]*m2.m[5] + m1.m[8]*m2.m[6]  + m1.m[12]*m2.m[7];
    mret.m[5] = m1.m[1]*m2.m[4] + m1.m[5]*m2.m[5] + m1.m[9]*m2.m[6]  + m1.m[13]*m2.m[7];
    mret.m[6] = m1.m[2]*m2.m[4] + m1.m[6]*m2.m[5] + m1.m[10]*m2.m[6] + m1.m[14]*m2.m[7];
    mret.m[7] = m1.m[3]*m2.m[4] + m1.m[7]*m2.m[5] + m1.m[11]*m2.m[6] + m1.m[15]*m2.m[7];

    mret.m[8]  = m1.m[0]*m2.m[8] + m1.m[4]*m2.m[9] + m1.m[8]*m2.m[10]  + m1.m[12]*m2.m[11];
    mret.m[9]  = m1.m[1]*m2.m[8] + m1.m[5]*m2.m[9] + m1.m[9]*m2.m[10]  + m1.m[13]*m2.m[11];
    mret.m[10] = m1.m[2]*m2.m[8] + m1.m[6]*m2.m[9] + m1.m[10]*m2.m[10] + m1.m[14]*m2.m[11];
    mret.m[11] = m1.m[3]*m2.m[8] + m1.m[7]*m2.m[9] + m1.m[11]*m2.m[10] + m1.m[15]*m2.m[11];

    mret.m[12] = m1.m[0]*m2.m[12] + m1.m[4]*m2.m[13] + m1.m[8]*m2.m[14]  + m1.m[12]*m2.m[15];
    mret.m[13] = m1.m[1]*m2.m[12] + m1.m[5]*m2.m[13] + m1.m[9]*m2.m[14]  + m1.m[13]*m2.m[15];
    mret.m[14] = m1.m[2]*m2.m[12] + m1.m[6]*m2.m[13] + m1.m[10]*m2.m[14] + m1.m[14]*m2.m[15];
    mret.m[15] = m1.m[3]*m2.m[12] + m1.m[7]*m2.m[13] + m1.m[11]*m2.m[14] + m1.m[15]*m2.m[15];
    return mret;
}

mat4 transposed(const mat4 &m)
{
    mat4 M = identity();
    M.m[0] = m.m[0];  M.m[4] = m.m[1];  M.m[8]  = m.m[2];  M.m[12] = m.m[3];
    M.m[1] = m.m[4];  M.m[5] = m.m[5];  M.m[9]  = m.m[6];  M.m[13] = m.m[7];
    M.m[2] = m.m[8];  M.m[6] = m.m[9];  M.m[10] = m.m[10]; M.m[14] = m.m[11];
    M.m[3] = m.m[12]; M.m[7] = m.m[13]; M.m[11] = m.m[14]; M.m[15] = m.m[15];
    return M;
}

mat4 rotation_mat(float angle, float x, float y, float z)
{
    mat4 mret = identity();
    float s = sin(angle);
    float c = cos(angle);

    mret.m[0] = x*x*(1-c)+c;
    mret.m[1] = y*x*(1-c)+z*s;
    mret.m[2] = x*z*(1-c)-y*s;

    mret.m[4] = x*y*(1-c)-z*s;
    mret.m[5] = y*y*(1-c)+c;
    mret.m[6] = y*z*(1-c)+x*s;

    mret.m[8] = x*z*(1-c)+y*s;
    mret.m[9] = y*z*(1-c)-x*s;
    mret.m[10] = z*z*(1-c)+c;

    return mret;
}

mat4 scale_mat(float x, float y, float z)
{
    mat4 mret = identity();
    mret.m[0] = x;
    mret.m[5] = y;
    mret.m[10] = z;
    return mret;
}

mat4 translation_mat(float x, float y, float z)
{
    mat4 mret = identity();
    mret.m[12] = x;
    mret.m[13] = y;
    mret.m[14] = z;
    return mret;
}

mat4 perspective(float fovy, float aspect, float znear, float zfar)
{
    mat4 M;
    float h = tan(fovy*0.017453293);
    float w = h / aspect;
    float depth = znear - zfar;
    float q = (zfar + znear) / depth;
    float qn = 2 * zfar * znear / depth;

    M.m[0]  = w;  M.m[1]  = 0;  M.m[2]  = 0;  M.m[3]  = 0;
    M.m[4]  = 0;  M.m[5]  = h;  M.m[6]  = 0;  M.m[7]  = 0;
    M.m[8]  = 0;  M.m[9]  = 0;  M.m[10] = q;  M.m[11] = -1;
    M.m[12] = 0;  M.m[13] = 0;  M.m[14] = qn;  M.m[15] = 0;


    return M;
}

mat4 ortho(float left, float right, float bottom, float  top, float n, float f)
{
    mat4 M = identity();
    M.m[0] = 2.0f/(right-left);
    M.m[5] = 2.0f/(top-bottom);
    M.m[10] = -2.0f/(f-n);
    M.m[12] = -(right+left)/(right-left);
    M.m[13] = -(top+bottom)/(top-bottom);
    M.m[14] = -(f+n)/(f-n);

    return M;
}

Frame::Frame()
{
    up = vec3{0,1,0};
    forward = vec3{0,0,-1};
    pos = vec3{0,0,0};
}

vec3 Frame::s()
{
    return cross(up, forward);
}

mat4 Frame::matrix(bool rotationOnly)
{
    mat4 M = identity();
    vec3 f = normal(forward);
    vec3 xx = normal(s());
    vec3 upp = normal(cross(forward, xx));

    M.m[0] = xx.x;    M.m[1] = xx.y;    M.m[2]  = xx.z;
    M.m[4] = upp.x;   M.m[5] = upp.y;   M.m[6]  = upp.z;
    M.m[8] = f.x;     M.m[9] = f.y;     M.m[10] = f.z;

    if( !rotationOnly )
    {
        M.m[12] = pos.x;    M.m[13] = pos.y;    M.m[14] = pos.z;
    }

    return M;
}


mat4 Camera::matrix(bool rotationOnly)
{
    mat4 M = identity();
    vec3 f = normal(forward);
    vec3 xx = normal(s());
    vec3 upp = normal(cross(xx, forward));
    M.m[0] = xx.x;    M.m[1] = upp.x;    M.m[2]  = -f.x;
    M.m[4] = xx.y;    M.m[5] = upp.y;    M.m[6]  = -f.y;
    M.m[8] = xx.z;    M.m[9] = upp.z;    M.m[10] = -f.z;

    if( !rotationOnly )
    {
        M = M*translation_mat(-pos.x, -pos.y, -pos.z);
    }

    return M;
}
