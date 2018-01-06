#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;

out vec2 textureCoordinates;
out vec3 pos;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(inPosition, 1.0);
	pos = worldPosition.xyz;
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	textureCoordinates = inTextureCoordinates;
}