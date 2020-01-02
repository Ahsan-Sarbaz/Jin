#version 440 core
out vec4 FinalColor;

struct Material
{
	vec4 Diffuse;
	int TextureBound;
	sampler2D Texture;
};

uniform Material mat;
in vec2 o_texCoord;

void main()
{
	if(mat.TextureBound == 1)
	{
		FinalColor = texture(mat.Texture, o_texCoord) * vec4(mat.Diffuse);
	}
	else
	{
		FinalColor = vec4(mat.Diffuse);
	}
}