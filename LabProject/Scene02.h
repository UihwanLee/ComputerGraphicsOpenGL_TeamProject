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

	Player* m_Player;

	Renderer* m_Renderer;

	CameraController* m_cameraController;

	ObjectManager* m_ObjectManager;

	Physics* m_Physics;

	unsigned char* m_texture;

	int				idx;
	int				curPickID;

	int				m_object01;
	int				m_object02;
	int				m_object03;

	int				m_table01; // 제단1
	int				m_table02; // 제단2

	int				m_statue; // 조각상

	int				m_door01;  // 문1
	int				m_door02;  // 문2

	vec3			CameraPos;

public:
	Scene02(CameraController*);
	~Scene02();

	void Init();
	void InitMap();
	void InitDoor();
	void InitObject();

	void Render();
	void Update(float elapsedTime);

	void InputKey(float elapsedTime);
	void InputMouse();

	void CheckRayCastingCollision();
	void ResetRayCastingCollision();
	bool CheckCollisionPlayerByWall(vec3 movePos);
	bool CheckCollisionPickObjByTable();
	void CheckDoor();
	void ApplyGravity();

private:
	void DrawView();
	void DrawViewByCamera();
	void DrawProjection();
	void DrawLight();

	void DrawObject(int DRAW_TYPE, glm::mat4& model, int idx);
	void DrawEndStage();
	void DrawStage2();

	void TextureMapping(ObjectType type);
};

