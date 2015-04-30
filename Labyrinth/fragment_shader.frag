#version 130

// in
in vec2 vs_out_texture;

//out
out vec4 fs_out_col;

//uniform
uniform sampler2D texture_image;
uniform bool isTheSunOrTheMoon;

void main()
{
	if (isTheSunOrTheMoon)
	{
		fs_out_col = vec4(1,1,0,1);
	}
	else
	{
		fs_out_col = texture(texture_image, vs_out_texture.st);
	}
}