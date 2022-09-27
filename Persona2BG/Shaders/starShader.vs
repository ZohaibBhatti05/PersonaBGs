#version 460 core

layout(location = 0) in vec2 iPos;

uniform mat4 transformations[11 * 15];
uniform float colors[11 * 15];
out float color;

void main()
{
	color = colors[gl_InstanceID];
	gl_Position = transformations[gl_InstanceID] * vec4(iPos, 0.0, 1.0);
}
