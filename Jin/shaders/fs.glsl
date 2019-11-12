#version 440 core
out vec4 FinalColor;

uniform vec4 u_Color;
in vec2 o_texCoord;
uniform sampler2D u_texture;

void main()
{
	FinalColor = texture(u_texture, o_texCoord) * vec4(u_Color);
}