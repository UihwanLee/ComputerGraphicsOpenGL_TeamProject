#include "pch.h"

#pragma once
class Scene02
{
private:
	GLuint			m_shaderProgramID = 0;
	GLuint			VBO_Test{};
	vector<vec3>	vTest;

public:
	Scene02(GLuint shaderProgramID);
	~Scene02();

	void Init();
	void Render(float elapsedTime);
	void Update(float elapsedTime);

private:

	void DrawEndStage(float elapsedTime);
	void DrawStage2(float elapsedTime);
};

