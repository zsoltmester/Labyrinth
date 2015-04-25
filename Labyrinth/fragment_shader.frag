#version 130

// in
in vec2 vs_out_texture_grass;

//out
out vec4 fs_out_col;

//uniform
uniform sampler2D texture_grass;

void main()
{
	fs_out_col = texture(texture_grass, vs_out_texture_grass.st);
}