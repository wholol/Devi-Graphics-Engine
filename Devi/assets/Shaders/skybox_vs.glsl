#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	texCoords = aPos;
	vec4 position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos,1.0);
	gl_Position = position.xyww;
}
