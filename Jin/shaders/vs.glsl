#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;



uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec2 o_texCoord;
out vec3 o_FragPos;
out mat4 o_ViewProjection;

void main()
{
	o_texCoord = texCoord;
	o_ViewProjection = u_ViewProjection;                                                                         
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1);
	o_FragPos = vec3(gl_Position);

}