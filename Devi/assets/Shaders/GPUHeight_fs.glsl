#version 460 core

in float height;
out vec4 fragColor;

in vec2 TexCoordFinal;
layout (binding = 1) uniform sampler2D grass;

void main()
{
	vec2 aTexCoordFinal = TexCoordFinal * 20;
	float m_height = height / 64.0f;

	fragColor = texture(grass, aTexCoordFinal);
}