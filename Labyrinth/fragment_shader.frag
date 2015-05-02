#version 130

// in
in vec3 vs_out_position;
in vec3 vs_out_normal;
in vec2 vs_out_texture;

//out
out vec4 fs_out_col;

//uniform
uniform sampler2D textureImage;

uniform bool isThisTheSunsVertex;
uniform bool isTheSunUp;

uniform vec3 eyePosition;
uniform vec3 sunPosition;

uniform vec4 ambientLightColor;
uniform vec4 sunDiffuseLightColor;
uniform vec4 sunSpecularLightColor;

uniform vec4 ambientLightStrength; 
uniform vec4 diffuseLightStrength;
uniform vec4 specularLightStrength;

uniform float specularLightSize;
uniform bool isASpecularMaterial;


void main()
{
	if (isThisTheSunsVertex)
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

		vec4 light = ambientLight;

		if (isTheSunUp)
		{
			light += diffuse;
			if (isASpecularMaterial)
			{
				light += specular;
			}
		}
		
		fs_out_col = light * texture(textureImage, vs_out_texture.st);
	} 
}