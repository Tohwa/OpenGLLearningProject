#version 330 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 UVs;

uniform sampler2D processingTexture;

void main()
{
	fragColor = texture(processingTexture, UVs);

	float brightness = dot(fragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	
	if(brightness > 1.0)
	{
		brightColor = vec4(fragColor.rgb, 1.0);
	}
	else
	{
		brightColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}