#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;	//technically ortho matrix for directional light.
uniform mat4 viewMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (aPos, 1.0);
}
