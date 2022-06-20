#version 460 core

uniform vec4 albedo;
out vec4 FragColor;

void main() 
{
	FragColor = albedo;
}