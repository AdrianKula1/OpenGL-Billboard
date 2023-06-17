#version 450

in vec2 uv;
uniform sampler2D textureSampler;

out vec4 color;

void main()
{
    color = texture(textureSampler, uv).rgba;
}

