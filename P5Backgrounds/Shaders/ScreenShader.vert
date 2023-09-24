#version 330 core

layout(location = 0) in vec4 iPositionUV;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(iPositionUV.xy, 0.0, 1.0);
	texCoord = iPositionUV.zw;
}