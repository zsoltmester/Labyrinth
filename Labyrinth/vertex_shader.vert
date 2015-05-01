#version 130

// in
in vec3 vs_in_position;
in vec3 vs_in_normal;
in vec2 vs_in_texture;

// out
out vec3 vs_out_position;
out vec3 vs_out_normal;
out vec2 vs_out_texture;

// uniform
uniform mat4 world;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vs_in_position, 1);
	
	vs_out_position = (world * vec4( vs_in_position, 1 )).xyz;
	vs_out_normal = vs_in_normal;
	vs_out_texture = vs_in_texture;
}