#version 330 core

out vec4 FragColour;

in VS_OUT{
    vec2 TexCoords;
    flat int index;
} fs_in;

uniform sampler2DArray text;
uniform int letterMap[200];

uniform vec3 textColour;
uniform float thickness = 0.7;
uniform float softness = 0.1;

uniform vec3 outlineColour = vec3(1.0, 0.0, 0.0);
uniform float outlineThickness = 0.0;
uniform float outlineSoftness = 0.1;


void main()
{    
    float alpha = texture(text, vec3(fs_in.TexCoords.xy,letterMap[fs_in.index])).r;
    float outline = smoothstep(outlineThickness - outlineSoftness, outlineThickness + outlineSoftness, alpha);
    alpha = smoothstep(1.0 - thickness - softness, 1.0 - thickness + softness, alpha);
    FragColour.rgb = mix(outlineColour, textColour, outline);
    FragColour.a = alpha;
}