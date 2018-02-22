#version 330

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inUV;

out vec2 textureCoordinates;

uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * vec4(inPosition, 0.0, 1.0);
	textureCoordinates = inUV;
}