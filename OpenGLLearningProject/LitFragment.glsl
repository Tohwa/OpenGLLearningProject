#version 330 core

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attConst;
	float attLin;
	float attQuad;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

out vec4 fragColor;

in vec4 vertexColor;
//in vec3 vertexNormals;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;

void main()
{
	fragColor = vertexColor;
}