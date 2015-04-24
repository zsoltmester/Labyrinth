#version 130

in vec3 vs_in_pos;

void main()
{
	gl_Position = vec4(vs_in_pos, 1);
}