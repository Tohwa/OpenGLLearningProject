#version 330 core
layout (location = 0) in vec3 pos;

in vec3 _pos;
in vec4 _color;

out vec4 vertexColor;

void main()
{
	gl_position = vec4(pos.x, pos.y, pos.z, 1.0f);
	vertexColor = _color;
}