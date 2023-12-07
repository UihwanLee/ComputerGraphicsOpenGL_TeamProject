#pragma once
#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "CameraController.h"
#include "Renderer.h"
#include "Physics.h"


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

	Physics*		m_Physics;

	unsigned char*	m_texture;

	int				idx;
	int				curPickID;

	int				m_table01; // Á¦´Ü1

public:
	Scene02(CameraController*);
	~Scene02();

	void Init();
	void InitMap();
	void InitObject();

	void Render();
	void Update(float elapsedTime);

	void InputKey(float elapsedTime);
	void InputMouse();

	void CheckRayCastingCollision();
	void ResetRayCastingCollision();
	bool CheckCollisionPlayerByWall(vec3 movePos);
	bool CheckCollisionPickObjByTable();
	void ApplyGravity();

private:
	void DrawView();
	void DrawProjection();
	void DrawLight();

	void DrawObject(int DRAW_TYPE, glm::mat4& model, int idx);
	void DrawEndStage();
	void DrawStage2();

	void TextureMapping(ObjectType type);
};

