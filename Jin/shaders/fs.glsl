#version 440 core
out vec4 FinalColor;

struct Material
{
	vec4 Diffuse;
	sampler2D Texture;
};

struct Light
{
	vec3 LightPos;
	vec3 LightColor;
};

uniform Light light;
uniform Material mat;

in vec2 o_texCoord;
in vec3 o_FragPos;
in mat4 o_ViewProjection;

void main()
{

	vec3 LightPos = vec3(o_ViewProjection * vec4(light.LightPos, 1));

	vec3 normal = vec3(0,0, 1);
	vec3 lightDir = normalize(LightPos - o_FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec4 DiffuseColor = diff * vec4(light.LightColor, 1);

	vec4 resultColor = mat.Diffuse * DiffuseColor;
	//FinalColor= vec4(lightDir, 1);
	FinalColor = texture(mat.Texture, o_texCoord) * resultColor;
}