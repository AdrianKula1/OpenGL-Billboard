#version 450

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 MaterialColor;

uniform sampler2D HMap;

uniform mat4 MVMat;
uniform mat4 MProj;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=2) in vec3 VertexNormals;
layout (location=3) in vec2 VertexUV;

out vec4 fColor;
out vec3 Normal;
out vec4 EyePos;
out vec2 uv;

void main()
{
    float y = texture(HMap, VertexUV).r;
    vec4 pos = vec4(VertexPosition, 1.0);
    pos.y = 0.5*y;
    gl_Position = MProj * MVMat * pos;
    mat3 NormalMat = mat3(MVMat);
    NormalMat = inverse(NormalMat);
    NormalMat = transpose(NormalMat);
    vec3 normal = normalize(NormalMat * VertexNormals);
    vec4 eyePos = MVMat * pos;

    ////////////////////////////////////////////
    //per vertex shading
//    vec4 light_mv = MVMat * vec4(LightPosition, 1);
//    //vec3 light = normalize(light_mv.xyz - eyePos.xyz);
//    vec3 light = normalize((LightPosition - eyePos.xyz));
//    float diff = max(0.0f, dot(normal, light));
//    vec3 r = reflect(light, normal);
//    vec3 v = vec3(0,0,-1);
//    float spec = pow( max(0.0f, dot(r,v)), 100);
//    fColor = vec4(MaterialColor * diff, 1.0) + vec4(1,1,1,1)*spec;

    ////////////////////////////////////////////
    //per fragment shading
    Normal = normal;
    EyePos = eyePos;
    uv = VertexUV;
    fColor = vec4(VertexColor,1);
}
