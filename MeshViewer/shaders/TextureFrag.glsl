#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Plight
{
	vec3 color;
	vec3 Pos;

	float linear;
	float quadratic;
	float constant;
};

struct Dlight
{
	vec3 color;
	vec3 Dir;
};

uniform Plight plights[16];
uniform int numPlights;

uniform Dlight dlights[16];
uniform int numDlights;

uniform float ambientStr;
uniform float specStr;
uniform vec3 color;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 calcPointLight(Plight plight, vec3 normal, vec3 fragpos, vec3 viewdir);
vec3 calcDirLight(Dlight dlight, vec3 normal, vec3 fragpos, vec3 viewdir);

void main()
{
		vec3 output = vec3(0.0);
		vec3 Norm = normalize(Normal);

		vec3 viewDir = normalize(viewPos - FragPos);

		for(int i = 0; i < numPlights; i++)
		{
			output += calcPointLight(plights[i], Norm, FragPos, viewDir);
		}

		for(int i = 0; i < numDlights; i++)
		{
			output += calcDirLight(dlights[i], Norm, FragPos, viewDir);
		}

		FragColor = vec4(output, 1.0);
}

vec3 calcPointLight(Plight plight, vec3 normal, vec3 fragpos, vec3 viewdir)
{
	float distance = length(fragpos - plight.Pos);

	float d2 = distance * distance;

	float attenuation = 1.0 / (plight.constant + (plight.linear * distance) + (plight.quadratic * d2));

	vec3 ambient = ambientStr * texture(texture_diffuse1, TexCoords).rgb;

	vec3 lightDir = normalize(plight.Pos - fragpos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * plight.color * texture(texture_diffuse1, TexCoords).rgb;

	vec3 halfwayDir = normalize(viewdir + lightDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), specStr); 

	vec3 specular = spec * plight.color * texture(texture_specular1, TexCoords).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (specular + diffuse + ambient);

	return result;
}

vec3 calcDirLight(Dlight dlight, vec3 normal, vec3 fragpos, vec3 viewdir)
{
	vec3 ambient = ambientStr * color;

	vec3 lightDir = normalize(-dlight.Dir);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * dlight.color * color;

	vec3 halfwayDir = normalize(viewdir + lightDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), specStr); 

	vec3 specular = spec * dlight.color * color;

	vec3 result = (specular + diffuse + ambient);

	return result;
}
