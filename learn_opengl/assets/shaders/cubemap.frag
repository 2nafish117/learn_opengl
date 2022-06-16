#version 330 core

in VS_OUT {
	vec3 uvw;
} fs_in;

out vec4 FragColor;

uniform samplerCube skybox;

void main() {
	FragColor = texture(skybox, fs_in.uvw);
}