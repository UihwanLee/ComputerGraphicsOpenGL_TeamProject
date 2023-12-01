#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoord;

out vec4 FragColor; 

uniform vec3 lightPos; 
uniform vec3 lightColor; 
uniform vec3 objectColor; 
uniform vec3 viewPos; 
uniform sampler2D outTexture;

uniform mat4 cameraTransform;

uniform vec3 pointLightPos[5];
float nPointLightPos = 5;

vec4 CalcLight(vec3 lightPos, vec3 lightColor)
{
	vec3 ambientLight = vec3(0.3f, 0.3f, 0.3f); 
	vec3 ambient = ambientLight * lightColor;
	vec3 lightTransPos = vec3((lightPos, 1.0));
	float d = distance(FragPos, lightPos);

	vec3 normalVector = normalize (Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor; 

	int shininess = 128; 
	vec3 viewDir = normalize(viewPos - FragPos); 
	vec3 reflectDir = reflect(-lightDir, normalVector); 
	float specularLight = max(dot(viewDir, reflectDir), 0.0); 
	specularLight = pow(specularLight, shininess); 
	vec3 specular = specularLight * lightColor; 

	vec3 result = ((ambient + diffuse + specular) / d)* objectColor; 

	return vec4(result, 1.0); 
}

void main()
{
	vec3 col1 = vec3(0.5f, 0.5f, 0.5f);
	vec4 TotalLight;

	for (int i = 0 ;i < nPointLightPos; i++) {
        TotalLight += CalcLight(pointLightPos[i], col1);
    }

	FragColor = TotalLight;
	FragColor = texture(outTexture, TextCoord) * FragColor;
}