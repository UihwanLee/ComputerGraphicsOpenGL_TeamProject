#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 FragPos;
out vec3 Normal; 
out vec2 TextCoord;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos,1.0);
    FragPos = vec3(modelTransform * vec4(vPos, 1.0));
    TextCoord = vTexCoord;

    Normal = mat3(transpose(inverse(modelTransform))) * vNormal;
}