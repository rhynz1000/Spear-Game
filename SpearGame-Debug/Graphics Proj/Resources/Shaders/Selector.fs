#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 Color;

uniform sampler2D SelTex;

void main()
{
    Color = texture(SelTex, fragTexCoord);
}
