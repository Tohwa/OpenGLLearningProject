#version 330 core
out vec4 fragColor;

in vec4 vertexColor;

uniform vec4 uniformColor;

void main()
{
	fragColor = uniformColor;
}