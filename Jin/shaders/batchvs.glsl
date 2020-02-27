#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texture;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec4 v_color;
out vec2 v_texCoord;
out float v_texture;

void main()
{
	v_color = color;
	v_texCoord = texCoord;
	v_texture = texture;
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1);
}