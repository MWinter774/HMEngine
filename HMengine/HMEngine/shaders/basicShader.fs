#version 450

layout (location = 1) in vec2 textureCoordinates;

out vec4 outColor;

void main()
{
	//gl_fragColor = vec4(1.0,0.0,0.0,1.0);
	outColor = vec4(1,0,0,1);

}