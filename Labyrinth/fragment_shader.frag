#version 130

// in
in vec2 vs_out_texture;

//out
out vec4 fs_out_col;

//uniform
uniform sampler2D texture_image;

void main()
{
	fs_out_col = texture(texture_image, vs_out_texture.st);
}