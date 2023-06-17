#version 450
uniform vec2 Resolution;
uniform vec3 Forward;

in vec4 fColor;
out vec4 FragColor;

void main()
{
    float v = 3.0 - 2.0*dot(Forward, vec3(Forward.x, 0, Forward.z));
    FragColor = fColor * v;
    //FragColor = fColor * gl_FragCoord.y/Resolution.y;
}
