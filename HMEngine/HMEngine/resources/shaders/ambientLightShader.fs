#version 330

in vec2 textureCoordinates;

out vec4 outColor;

uniform sampler2D sampler;
uniform vec3 ambientLight;
uniform vec3 skyColor;

in float visibilty;

void main()
{
	outColor = texture2D(sampler, textureCoordinates) * vec4(ambientLight, 1.0f);
	outColor = mix(vec4(skyColor, 1.0), outColor, visibilty);
}