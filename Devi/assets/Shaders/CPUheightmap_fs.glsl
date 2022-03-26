#version 330 core

out vec4 FragColor;
in float height;

void main()
{
	float heightcol = height;

	FragColor= vec4(heightcol / 64,heightcol/ 64,heightcol/ 64,1.0);
}

