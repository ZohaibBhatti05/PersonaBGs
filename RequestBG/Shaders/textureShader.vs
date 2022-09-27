#version 460 core
layout(location = 0) in vec2 iPos;
layout(location = 1) in vec2 iTexCoord;

uniform mat4 transformation;
out vec2 TexCoord;

void main()
{
	TexCoord = iTexCoord;
	gl_Position = transformation * vec4(iPos, 0.0, 1.0);
}