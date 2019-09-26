#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

void main(void)
{
	gl_Position = vec4(Position, 1.0);
	fragColor = Color;
	fragTexCoord = TexCoord;
}
