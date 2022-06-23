#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

layout (binding = 6) uniform sampler2D heightMap;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 clippingPlane;

in vec2 TextureCoord[];

out vec2 TexCoordFinal;
out float height;
out vec4 CurrentPositionFromLightPerspectiveNDC;
out vec3 WorldPos;
out vec3 normals;

void main()
{
	//get the tesselation coordiantes (newly generated coordinate)
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	//texture coordiantes of the heightmap
	vec2 tex01 = TextureCoord[0];
	vec2 tex02 = TextureCoord[1];
	vec2 tex03 = TextureCoord[2];
	vec2 tex04 = TextureCoord[3];

	//now we lerp binearlly to get the texture coordinates of the new vertices.
	//lerp the two parallel sides first
	vec2 tex1 = (tex02 - tex01) * u + tex01;
	vec2 tex2 = (tex04 - tex03) * u + tex03;

	//now that we have both sides for the tex coords, lerp to find the center between them.
	vec2 finalTextureCoord = (tex2 - tex1) * v + tex1;

	TexCoordFinal = finalTextureCoord;

	height = texture(heightMap, finalTextureCoord).y * 260.0;

	//since we set the vertexbuffers to have y to be zero, we are having only a flat mesh. the way we perform the terrain height is by displacement mapping.
	//get the positions of the quad.
	vec4 position1 = gl_in[0].gl_Position;
	vec4 position2 = gl_in[1].gl_Position;
	vec4 position3 = gl_in[2].gl_Position;
	vec4 position4 = gl_in[3].gl_Position;

	vec4 distance1 = position2 - position1;
	vec4 distance2 = position3 - position1;

	//really this is just a normal pointing straight up.
	vec4 normal = normalize( vec4( cross(distance2.xyz, distance1.xyz), 0) );

	vec4 currentpos1 = (position2 - position1) * u + position1;
	vec4 currentpos2 = (position4 - position3) * u + position3;

	vec4 currentposition = (currentpos2 - currentpos1) * v + currentpos1;
	vec4 displacementVector = normal * height;	//we're scaling the height here.
	currentposition += displacementVector;

	WorldPos = vec3(modelMatrix * currentposition);
	normals = vec3(normal);

	gl_ClipDistance[0] = dot(clippingPlane, vec4(WorldPos, 1.0));

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * currentposition;

}