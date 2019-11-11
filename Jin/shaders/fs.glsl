#version 440 core
out vec4 FinalColor;

uniform vec4 u_Color;

void main()
{
	FinalColor = vec4(u_Color);
}