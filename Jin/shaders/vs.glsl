#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;



uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec2 v_texCoord;
out vec3 v_FragPos;
out mat4 v_ViewProjection;

void main()
{
	v_texCoord = texCoord;
	v_ViewProjection = u_ViewProjection;
	gl_Position = u_ViewProjection * u_Transform  * vec4(position, 1);
	v_FragPos = gl_Position.xyz;
}