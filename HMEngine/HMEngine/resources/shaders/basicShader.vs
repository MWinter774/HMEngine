#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;

out vec2 textureCoordinates;
out vec3 pos;
out float visibilty;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float fogDensity;
uniform float fogGradient;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(inPosition, 1.0);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	pos = worldPosition.xyz;
	gl_Position = projectionMatrix * positionRelativeToCamera;
	textureCoordinates = inTextureCoordinates;
	
	float distanceToCamera = length(positionRelativeToCamera.xyz);
	visibilty = clamp(exp(-pow((distanceToCamera * fogDensity), fogGradient)), 0.0, 1.0);
	
}