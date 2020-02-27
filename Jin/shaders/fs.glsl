#version 440 core
out vec4 FinalColor;

struct Material
{
	vec4 Diffuse;
	sampler2D Texture;
};

struct Light
{
	vec3 Pos;
	vec3 Color;
};

uniform Light light;
uniform Material mat;

in vec2 v_texCoord;
in vec3 v_FragPos;
in mat4 v_ViewProjection;

uniform vec3  u_intensity;        // intensity value to apply to the light
uniform float u_attenuation_c;    // constant attenuation
uniform float u_attenuation_l;    // linear attenuation
uniform float u_attenuation_q;    // quadratic attenuation

void main()
{
	vec4 lightPos = v_ViewProjection * vec4(light.Pos, 1);
	float d = distance(lightPos.xyz, v_FragPos);

	vec3 frag_intensity = u_intensity / (u_attenuation_c + u_attenuation_l*d + u_attenuation_q*pow(d,2));

	FinalColor = vec4(frag_intensity * light.Color, 1) * texture(mat.Texture, v_texCoord);
}