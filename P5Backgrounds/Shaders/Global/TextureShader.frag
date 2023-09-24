#version 330 core

in vec2 texCoord;
out vec4 FragColour;

uniform sampler2D Texture;

void main()
{
	FragColour = texture(Texture, texCoord);
	if (FragColour.a < 0.05)
	{
		discard;
	}
}