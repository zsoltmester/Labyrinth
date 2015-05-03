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

uniform bool isThisAFieldWithAPortal = false;
uniform vec3 portalLightSourcePosition;


void main()
{
	if (isThisTheSunsVertex)
	{
		fs_out_col = vec4(1, 1, 0, 1); // TODO move to the config
	}
	else if (isThisTheMoonsVertex)
	{
		fs_out_col = vec4(0.5f, 0.5f, 0.5f, 1); // TODO move to the config
	}
	else
	{
		bool isTheSunUp = sunPosition.y > 0;
		bool isTheMoonUp = moonPosition.y > 0;

		vec3 orbPosition = isTheMoonUp ? moonPosition : sunPosition;
		vec4 diffuseLightColor = isTheMoonUp ? moonDiffuseLightColor : sunDiffuseLightColor;
		vec4 specularLightColor = isTheMoonUp ? moonSpecularLightColor : sunSpecularLightColor;

		vec3 normal = normalize(vs_out_normal);
		vec3 lightDirectionToPosition = normalize(orbPosition - vs_out_position);

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

		//
		// portal
		//

		if (isThisAFieldWithAPortal)
		{
			lightDirectionToPosition = normalize(portalLightSourcePosition - vs_out_position);

			// diffuse light
			di = clamp(dot(lightDirectionToPosition, normal), 0.0f, 1.0f);
			diffuse = vec4(1, 0, 0, 1) * di; // TODO move to the config

			// specular light
			r = reflect(-lightDirectionToPosition, normal);
			si = pow(clamp(dot(eyeDirectionToPosition, r), 0.0f, 1.0f ), specularLightSize);
			specular = vec4(1, 0, 0, 1) * si; // TODO move to the config

			vec4 portalLight = diffuse;
			if (isASpecularMaterial)
			{
				portalLight += specular;
			}

			light += portalLight;
		}
		
		fs_out_col = light * texture(textureImage, vs_out_texture.st);
	} 
}