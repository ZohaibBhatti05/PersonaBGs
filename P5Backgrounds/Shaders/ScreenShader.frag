#version 330 core

in vec2 texCoord;
out vec4 FragColour;

uniform sampler2D screenTexture;

void main()
{
	FragColour = texture(screenTexture, texCoord);
}