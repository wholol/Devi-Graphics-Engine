#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out float height;

void main()
{
    height = aPos.y;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}