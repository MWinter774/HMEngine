#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;
layout (location = 2) in vec3 inNormals;

out vec2 textureCoordinates;
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
	gl_Position = projectionMatrix * positionRelativeToCamera;
	
	float distanceToCamera = length(positionRelativeToCamera.xyz);
	
	// pass to fragment shader
	textureCoordinates = inTextureCoordinates;
	visibilty = clamp(exp(-pow((distanceToCamera * fogDensity), fogGradient)), 0.0, 1.0);
	
}