#pragma once
#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "CameraController.h"
#include "Renderer.h"


class Scene02
{
private:
	GLuint			m_shaderProgramID = 0;
	GLuint			VBO[3];
	GLuint			texture;

	Camera			camera;
	Player*			m_Player;
	Renderer*		m_Renderer;

	CameraController* m_cameraController;

	ObjectManager*	m_ObjectManager;

	unsigned char*	m_texture;

	int				idx;

public:
	Scene02(CameraController*);
	~Scene02();

	void Init();
	void InitMap();
	void InitObject();

	void Render();
	void Update(float elapsedTime);

private:
	void DrawView();
	void DrawProjection();
	void DrawLight();

	void DrawObject(int DRAW_TYPE, glm::mat4& model, int idx);
	void DrawEndStage();
	void DrawStage2();

	void TextureMapping(ObjectType type);
};

