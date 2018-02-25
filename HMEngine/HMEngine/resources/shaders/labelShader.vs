#version 330

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inUV;

out vec2 textureCoordinates;

uniform vec2 translation;

void main()
{
	gl_Position = vec4(inPosition + translation * vec2(2.0f, -2.0f), 0.0, 1.0);
	textureCoordinates = inUV;
}