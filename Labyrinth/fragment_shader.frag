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
uniform bool isThisTheMoonsVertex;

uniform vec3 eyePosition;
uniform vec3 sunPosition;
uniform vec3 moonPosition;

uniform vec4 ambientLightColor;
uniform vec4 ambientLightStrength; 

uniform vec4 sunDiffuseLightColor;
uniform vec4 moonDiffuseLightColor;
uniform vec4 diffuseLightStrength;

uniform vec4 sunSpecularLightColor;
uniform vec4 moonSpecularLightColor;
uniform vec4 specularLightStrength;

uniform float specularLightSize;
uniform bool isASpecularMaterial;


void main()
{
	if (isThisTheSunsVertex)
	{
		fs_out_col = vec4(1, 1, 0, 1); // yellow
	}
	else if (isThisTheMoonsVertex)
	{
		fs_out_col = vec4(0.5f, 0.5f, 0.5f, 1); // grey
	}
	else
	{
		bool isTheSunUp = sunPosition.y > 0;
		bool isTheMoonUp = moonPosition.y > 0;

		vec3 currentPosition = isTheMoonUp ? moonPosition : sunPosition;
		vec4 diffuseLightColor = isTheMoonUp ? moonDiffuseLightColor : sunDiffuseLightColor;
		vec4 specularLightColor = isTheMoonUp ? moonSpecularLightColor : sunSpecularLightColor;

		vec3 normal = normalize(vs_out_normal);
		vec3 lightDirectionToPosition = normalize(currentPosition - vs_out_position);

		//
		// ambient light
		//
		
		vec4 ambientLight = ambientLightStrength * ambientLightColor;

		//
		// diffuse light
		//

		float di = clamp(dot(lightDirectionToPosition, normal), 0.0f, 1.0f);
		vec4 diffuse = diffuseLightColor * diffuseLightStrength * di;

		//
		// specular light
		//

		vec3 eyeDirectionToPosition = normalize(eyePosition - vs_out_position);
		vec3 r = reflect(-lightDirectionToPosition, normal);
		float si = pow(clamp(dot(eyeDirectionToPosition, r), 0.0f, 1.0f ), specularLightSize);
		vec4 specular = specularLightColor * specularLightStrength * si;

		vec4 light = ambientLight;

		if (isTheSunUp || isTheMoonUp)
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