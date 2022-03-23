#version 330 core

in vec3 texCoords;
out vec4 FragColor;

uniform samplerCube CubeMap;

void main()
{
	FragColor = texture(CubeMap,texCoords);
}
