#version 330 core

in VS_OUT{
    vec2 uv0;
} fs_in;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, fs_in.uv0);
}