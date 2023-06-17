#version 450

uniform sampler2D DiffuseTex;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 MaterialColor;

in vec4 fColor;
in vec3 Normal;
in vec4 EyePos;
in vec2 uv;

out vec4 FragColor;

void main()
{
    ////////////////////////////////////////////
    //per vertex shading
    //FragColor = fColor;

    ////////////////////////////////////////////
    //per fragment shading
    vec3 light = normalize(LightPosition-EyePos.xyz);
    vec3 normal = normalize(Normal);
    float diff = max(0.0f, dot(normal, light));
    vec3 r = reflect(-light, normal);
    vec3 v = normalize(-EyePos.xyz);
    float spec = pow( max(0.0f, dot(r,v)), 20);

    vec4 tex = texture(DiffuseTex, uv);
    //FragColor = diff * tex * vec4(MaterialColor, 1.0) + vec4(1,1,1,1)*spec;
    FragColor = diff * fColor*vec4(MaterialColor, 1.0) + vec4(1,1,1,1)*spec;
}
