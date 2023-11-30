#pragma once
#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "CameraController.h"
#include "LightController.h"


class Scene02
{
private:
	GLuint			m_shaderProgramID = 0;
	GLuint			VBO[3];
	GLuint			texture;

	Camera			camera;
	Light			light;
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

	void DrawObject(int DRAW_TYPE, glm::mat4& model, int idx);
	void DrawEndStage(float elapsedTime);
	void DrawStage2(float elapsedTime);
};

