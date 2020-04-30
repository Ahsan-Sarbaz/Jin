#version 400
out vec4 FinalColor;

in vec4  v_color;
in vec2  v_texCoord;

uniform sampler2D u_fontTexture;

void main()
{	
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_fontTexture, v_texCoord).r);
    FinalColor = vec4(v_color.rgb, 1.0) * sampled;
}
