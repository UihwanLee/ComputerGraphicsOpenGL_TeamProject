#include "pch.h"

#pragma once
class Scene01
{
private:
	GLuint			m_shaderProgramID = 0;
	GLuint			VBO[2];
	vector<vec3>	vTest;

public:
	Scene01(GLuint shaderProgramID);
	~Scene01();

	void Init();
	void Render(float elapsedTime);
	void Update(float elapsedTime);
	
private:
	void DrawStartStage(float elapsedTime);
	void DrawStage1(float elapsedTime);

	void CreateVertexBufferObjectBox();

private:
	// 변환 파이프라인
};

