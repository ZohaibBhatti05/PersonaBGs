#version 330 core
layout (location = 0) in vec2 iPos; // <vec2 pos>

out VS_OUT{
    vec2 TexCoords;
    flat int index;
} vs_out;

uniform mat4 transformations[200];
uniform mat4 projection;

void main()
{
    gl_Position = projection * transformations[gl_InstanceID]* vec4(iPos, 0.0, 1.0);
    vs_out.index=gl_InstanceID;
    vs_out.TexCoords = iPos.xy;
    vs_out.TexCoords.y = 1.0f - vs_out.TexCoords.y;
}