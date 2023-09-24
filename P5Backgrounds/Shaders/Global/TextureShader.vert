#version 330 core

layout(location = 0) in vec2 iPosition;
layout(location = 1) in vec2 iUV;

out vec2 texCoord;

uniform mat4 transformation;

void main()
{
	gl_Position = transformation * vec4(iPosition, 0.0, 1.0);
	texCoord = iUV;
}