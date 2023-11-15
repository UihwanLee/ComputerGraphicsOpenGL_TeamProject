#version 330 core

in vec3 in_Position; 

uniform mat4 model;

void main(void) 
{
	gl_Position =  model * vec4 (in_Position, 1.0);
	
	
}