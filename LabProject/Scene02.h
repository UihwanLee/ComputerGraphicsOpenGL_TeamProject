#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"

#pragma once
class Scene02
{
private:
	GLuint			m_shaderProgramID = 0;
	GLuint			VBO[2];

	Player*			m_Player;
	ObjectManager*	m_ObjectManager;

public:
	Scene02(GLuint shaderProgramID);
	~Scene02();

	void Init();
	void Render(float elapsedTime);
	void Update(float elapsedTime);

private:
	void DrawView();
	void DrawProjection();
	void DrawPlayerLight();

	void DrawPlayer();
	void DrawObject(int DRAW_TYPE, glm::mat4& model, int idx);
	void DrawEndStage(float elapsedTime);
	void DrawStage2(float elapsedTime);
};

