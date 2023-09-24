#version 330 core

layout(location = 0) in vec2 i_Pos;

uniform mat4 transformations[11 * 18];
uniform vec3 colours[11 * 18];
out vec3 colour;

void main()
{
	colour = colours[gl_InstanceID];
	gl_Position = transformations[gl_InstanceID] * vec4(i_Pos, 0.0, 1.0);
}
