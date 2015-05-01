#version 130

// in
in vec3 vs_out_position;
in vec3 vs_out_normal;
in vec2 vs_out_texture;

//out
out vec4 fs_out_col;

//uniform
uniform sampler2D textureImage;
uniform bool isTheSunOrTheMoon;

uniform vec3 eyePosition;
uniform vec3 sunPosition;

// TODO move these to config
uniform vec4 ambientLightColor = vec4(1, 1, 1, 1);
uniform vec4 sunDiffuseLightColor = vec4(1, 1, 0, 1);
uniform vec4 sunSpecularLightColor = vec4(1, 1, 0, 1);

// TODO move these to config
uniform vec4 ambientLightStrength = vec4(0.1f, 0.1f, 0.1f, 1); 
uniform vec4 diffuseLightStrength = vec4(0.5f, 0.5f, 0.5f, 1);
uniform vec4 specularLightStrength = vec4(1, 1, 1, 1);

// file visibility
// TODO move this to config
float specularLightSize = 24;

void main()
{
	if (isTheSunOrTheMoon)
	{
		fs_out_col = vec4(1, 1, 0, 1); // yellow
	}
	else
	{
		vec3 normal = normalize(vs_out_normal);
		vec3 lightDirectionToPosition = normalize(sunPosition - vs_out_position);

		//
		// ambient light
		//
		
		vec4 ambientLight = ambientLightStrength * ambientLightColor;

		//
		// diffuse light
		//

		float di = clamp(dot(lightDirectionToPosition, normal), 0.0f, 1.0f);
		vec4 diffuse = sunDiffuseLightColor * diffuseLightStrength * di;

		//
		// specular light
		//

		vec3 eyeDirectionToPosition = normalize(eyePosition - vs_out_position);
		vec3 r = reflect(-lightDirectionToPosition, normal);
		float si = pow(clamp(dot(eyeDirectionToPosition, r), 0.0f, 1.0f ), specularLightSize);
		vec4 specular = sunSpecularLightColor * specularLightStrength * si;


		fs_out_col = (ambientLight + diffuse + specular) * texture(textureImage, vs_out_texture.st);
	}
}