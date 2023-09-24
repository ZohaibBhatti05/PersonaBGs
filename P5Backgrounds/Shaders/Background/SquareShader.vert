#version 330 core
layout(location = 0) in vec2 iPos;
layout(location = 1) in vec2 iTexCoord;

uniform mat4 transformations[38];
uniform vec3 colours[38];
out vec3 colour;

void main()
{
	colour = colours[gl_InstanceID];
	gl_Position = transformations[gl_InstanceID] * vec4(iPos, 0.0, 1.0);
}


