#version 450

uniform vec3 Color;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;

out vec4 fColor;

void main()
{
    gl_Position = vec4(VertexPosition, 1.0);
    fColor = vec4(VertexColor, 1.0);
}
