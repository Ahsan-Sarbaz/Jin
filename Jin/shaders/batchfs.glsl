#version 440 core
out vec4 FinalColor;

in vec4  v_color;
in vec2 v_texCoord;
in float v_texture;


uniform sampler2D tex;

void main()
{
	FinalColor = texture(tex, v_texCoord) * v_color;
	//FinalColor = v_color;
}