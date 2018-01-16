#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 normal;

out vec2 textureCoordinates0;
out vec3 surfaceNormal;
out vec3 worldPosition0;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main()
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	worldPosition0 = worldPosition.xyz;
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	textureCoordinates0 = textureCoordinates;
	
	surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
	
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}