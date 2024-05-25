#version 330 core

in vec2 _Pos;
in vec2 _UVs;

out vec2 UVs;

void main()
{
	gl_Position = vec4(_Pos, 0.0, 1.0);
	UVs = _UVs;
}
