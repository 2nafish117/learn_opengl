#version 330 core
layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec3 uvw;
} vs_out;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
};

void main()
{
    vs_out.uvw = aPos;
    vec4 position = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = position.xyww;
}
