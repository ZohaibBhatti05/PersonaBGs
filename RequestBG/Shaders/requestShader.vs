#version 460 core
layout(location = 0) in vec2 iPos;
layout(location = 1) in vec2 iTexCoord;

uniform mat4 transformations[38];
uniform vec3 colors[38];
out vec3 color;

void main()
{
	color = colors[gl_InstanceID];
	gl_Position = transformations[gl_InstanceID] * vec4(iPos, 0.0, 1.0);
}


