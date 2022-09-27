#version 460 core
out vec4 FragColor;

uniform sampler2D Texture;
in vec2 TexCoord;

void main()
{
	FragColor = texture(Texture, TexCoord);

	if (FragColor.a < 0.1)
	{
		discard;
	}
}