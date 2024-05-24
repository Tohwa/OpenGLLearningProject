#version 330 core

 out vec4 FragColor;

 in vec2 UVs;

 uniform sampler2D hdrTex;
 uniform sampler2D blurTex;
 uniform float exposure = 1;

 void main()
 {
	const float gamma = 2.2;
	vec3 hdrColor = texture(hdrTex, UVs).rgb;
	vec3 bloomColor = texture(blurTex, UVs).rgb;
	hdrColor += bloomColor; // additive blending
	// tone mapping
	vec3 result = vec3(1.0)- exp(-hdrColor * exposure);
	// also gamma correct while we’re at it
	result = pow(result, vec3(1.0 / gamma));
	FragColor = vec4(result, 1.0);

 }
