#version 330 core
layout (location = 0) in vec2 _UVs;

out vec2 UVs;

void main()
{
	UVs = _UVs;
}
