#version 330 core

struct Light
{
    vec3 position;
	vec3 ambient; //ambient intensity
	vec3 diffuse; //basecolor
	vec3 specular; //specular color

	float attConst;
	float attLin;
	float attQuad;
};

struct Material
{
	vec3 ambient; //basecolor
	vec3 diffuse; //basecolor
	vec3 specular; //reflection
	float shininess; //intensity
};

out vec4 fragColor;

in vec4 vertexColor;
in vec3 vertexNormal;
in vec3 vertexPos;
in vec2 vertexUV;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;
uniform sampler2D diffuseTexture;

vec3 CalculateAmbient()
{
	return light.ambient * texture(diffuseTexture, vertexUV).xyz;
}

vec3 CalculateDiffuse()
{
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - vertexPos);
	float intensity = max(dot(lightDir, normal), 0.0);

	return light.diffuse * (texture(diffuseTexture, vertexUV).xyz * intensity);
}

vec3 CalculateSpecular()
{
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - vertexPos);
	vec3 viewDir = normalize(cameraPosition - vertexPos);

	vec3 reflection = reflect(-lightDir, normal);

	float specIntensity = pow(max(dot(viewDir, reflection), 0.0), 32.0);

	return light.specular * (material.specular * specIntensity);
}

float CalculateAttenuation()
{
	float distance = length(light.position - vertexPos);

	return 1.0/(light.attConst + (light.attLin * distance) + (light.attQuad * distance * distance));
}

void main()
{
	vec3 ambient = CalculateAmbient();
	vec3 diffuse = CalculateDiffuse();
	vec3 specular = CalculateSpecular();
	
	float attenuation = CalculateAttenuation();

	vec4 resultColor = vec4(((ambient + diffuse + specular) * attenuation) /* / 3 */, 1.0);

	fragColor = resultColor;
}