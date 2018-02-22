#version 330

in vec2 textureCoordinates;

uniform sampler2D sampler;

out vec4 outColor;

void main(void)
{
    outColor = vec4(vec3(1, 0, 0), 1.0) * vec4(1.0, 1.0, 1.0, texture2D(sampler, textureCoordinates).r);
}