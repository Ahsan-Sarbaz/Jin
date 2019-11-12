#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_Tranform;
uniform mat4 u_Projection;

out vec2 o_texCoord;

void main()
{
	o_texCoord = texCoord;
	gl_Position = u_Projection * u_Tranform * vec4(position, 1);
}