#version 330 core

in vec3 FragPos; 
in vec3 Normal;
in vec2 TextCoord;

out vec4 FragColor;  

uniform vec3 lightPos;
uniform vec3 lightdirection;
uniform vec2 lightcutoff;
uniform vec3 attenuation; 
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform vec3 objectColor;
uniform sampler2D outTexture;

uniform vec3 pointLightPos[20];
float nPointLightPos = 20;

vec4 CalcPointLight(vec3 lightPos, vec3 lightColor)
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

vec4 CalcPlayerLight()
{
    float ambientLight = 0.1f;
    vec3 ambient = ambientLight * lightColor;

    float dist = length(lightPos - FragPos);
    vec3 distPoly = vec3(1.0, dist, dist*dist);
    float attenuation = 1.0 / dot(distPoly, attenuation);
    vec3 lightDir = (lightPos - FragPos) / dist;

    vec3 result = ambient;
    float theta = dot(lightDir, normalize(-lightdirection));
    float intensity = clamp(
        (theta - lightcutoff[1]) / (lightcutoff[0] - lightcutoff[1]),
        0.0, 1.0);

    if(intensity > 0.f)
    {
        vec3 normalVector = normalize(Normal);
        float diffuseLight = max(dot(normalVector, lightDir), 0.0);
        vec3 diffuse = diffuseLight * lightColor;

        int shininess = 256;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, normalVector);
        float specularLight = max(dot(viewDir, reflectDir), 0.0);
        specularLight = pow(specularLight, shininess);
        vec3 specular = specularLight * lightColor;
        result += (diffuse + specular) * intensity;
    }
    result *= attenuation;
    return vec4(result, 1.0f);
}

void main()
{
    vec3 col1 = vec3(0.5f, 0.5f, 0.5f);
	vec4 TotalLight;
    vec4 PlayerLight;

	for (int i = 0 ;i < nPointLightPos; i++) {
        TotalLight += CalcPointLight(pointLightPos[i], col1);
    }

    PlayerLight = CalcPlayerLight();

	FragColor = TotalLight + PlayerLight;
	FragColor = texture(outTexture, TextCoord) * FragColor;

}