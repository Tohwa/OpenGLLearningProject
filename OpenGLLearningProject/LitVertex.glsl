#version 330 core

in vec3 _pos;
in vec4 _col;
in vec3 _nor;
in vec2 _uv;

out vec4 vertexColor;
out vec3 vertexNormal;
out vec2 vertexUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;
void main()
{
	gl_Position = projection * view * model * vec4(_pos, 1.0);
	vertexColor = _col;
}