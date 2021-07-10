#version 330 core
out vec4 FragColor;

in vec3 vs_outColor;

uniform int u_test;

void main()
{
	FragColor = vec4(vs_outColor, 1.0f);
};