#version 130

// in
in vec3 vs_in_position;
in vec2 vs_in_texture_grass;

// out
out vec2 vs_out_texture_grass;

// uniform
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vs_in_position, 1);

	vs_out_texture_grass = vs_in_texture_grass;
}