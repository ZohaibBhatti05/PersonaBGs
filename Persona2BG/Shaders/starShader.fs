#version 460 core
out vec4 FragColor;

in float color;

void main()
{
	FragColor = vec4(color, color, color, 1.0);
}