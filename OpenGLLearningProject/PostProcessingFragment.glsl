#version 330 core

out vec4 fragColor;

in vec2 UVs;

uniform sampler2D processingTexture;

void main()
{
	fragColor = texture(processingTexture, UVs);
}