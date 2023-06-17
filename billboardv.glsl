#version 450

uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;



uniform mat4 MVMat;
uniform mat4 MProj;

uniform vec2 Size;
uniform vec3 Position;


layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 VertexUV;

out vec2 uv;

void main()
{

    vec3 vertexPosition_worldspace =
        Position
        + CameraUp_worldspace * VertexPosition.x * Size.x
        + CameraRight_worldspace * VertexPosition.y * Size.y;


    gl_Position = MProj * MVMat * vec4(vertexPosition_worldspace, 1.0f);
    uv = VertexUV;
}
