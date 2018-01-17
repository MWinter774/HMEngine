#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;
layout (location = 2) in vec3 inNormals;

out vec2 textureCoordinates;
out vec3 normals;
out vec3 worldPosition;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 worldPosition0 = transformationMatrix * vec4(inPosition, 1.0);
	worldPosition = worldPosition0.xyz;
	gl_Position = projectionMatrix * viewMatrix * worldPosition0;
	
	//pass to fragmentShader
	textureCoordinates = inTextureCoordinates;
	normals = (transformationMatrix * vec4(inNormals, 0.0)).xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition0.xyz;
}