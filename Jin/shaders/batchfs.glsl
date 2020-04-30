#version 400
out vec4 FinalColor;

in vec4  v_color;
in vec2  v_texCoord;
in float v_texSlot;

uniform sampler2D u_textures[16];

void main()
{
	int slot = int(v_texSlot);
    FinalColor = texture(u_textures[slot], v_texCoord) * v_color;
}
