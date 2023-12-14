#pragma once

#include "Player.h"
#include "Scene01.h"
#include "Scene02.h"

#include "OBJModel.h"
#include "Camera.h"
#include "Types.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();


	void DrawCubeObj(CameraController*, vec3 position, vec3 rotate, vec3 size, ObjectType type);
	void DrawRintyObj(CameraController*, vec3 position, vec3 rotate, vec3 size, float radian);
	void DrawFlashObj(CameraController*, vec3 position, vec3 size);


private:
	bool IsInitialized();
	void ConvertToOpenGL(int x, int y, float* ox, float* oy);
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(const char* filename, std::string* target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(const char* filenameVS, const char* filenameFS);
	void InitTexture();

	// 초기 쉐이더 위치들 작업
	void InitShaderLocation();

private:
	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint shaderProgramID = 0;

	GLuint cubeVBO{};
	vector<vec3> vCube;

	// obj 모델
	OBJModel model;
	int vertexCount;
	GLuint objVBO;

	int vertexCountRinty;
	GLuint objRinty;

	int vertexCountFlash;
	GLuint objFlash;


	// texture 관련
	unsigned int m_CubeTexture[6];

	// shader location
	GLint AttributePosition;
	GLint AttributeNormal;
	GLint AttributeTexutre;

	unsigned int modelMat;
	unsigned int viewMat;
	unsigned int projMat;
	unsigned int pLightPos;
	unsigned int pLightColor;
	unsigned int pViewPos;
	unsigned int atten;
	unsigned int lightdirection;
	unsigned int lightcutoff;
	unsigned int fTexture;

	// 조명
	vec2 cutoff;

public:
	// =============================
	GLuint GetShaderProgramID() { return shaderProgramID; }

};
