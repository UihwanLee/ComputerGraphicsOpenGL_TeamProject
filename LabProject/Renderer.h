#pragma once

#include "Object.h"
#include "Player.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();

	void ConvertToOpenGL(int x, int y, float* ox, float* oy);

	void DrawAll(float elapsedTime);
	void UpdateAll(float elapsefTime);

	GLuint GetShaderProgramID() { return shaderProgramID; }

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(const char* filename, std::string* target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(const char* filenameVS, const char* filenameFS);

private:
	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint shaderProgramID = 0;
	GLuint VBO_Test{};
	vector<vec3> vTest;
};
