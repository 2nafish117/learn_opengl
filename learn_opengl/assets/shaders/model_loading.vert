#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 uv0;
} vs_out;

layout (std140) uniform Matrices {
    uniform mat4 projection;
    uniform mat4 view;
};

uniform mat4 model;

void main()
{
    vs_out.uv0 = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}