#pragma once

#include "pch.h"
#include "CameraController.h"
#include "Object.h"
#include "Player.h"

class ObjectManager
{
public:
	ObjectManager();
	ObjectManager(CameraController* cameraController);
	~ObjectManager();

	void Init(CameraController*);

	int GetRandomIntValue(GLfloat min, GLfloat max);
	GLfloat GetRandomFloatValue(GLfloat min, GLfloat max);

	void CreateFigure(Object* gameObject, highp_vec3 color);
	void CreateCube(int* idx, highp_vec3 color, ObjectType type);
	void CreateSqhere(int* idx, highp_vec3 color, ObjectType type);
	void CreatStatue(int* idx, highp_vec3 color, ObjectType type);

	void SetPosition(int idx, float x, float y, float z);
	void SetRotate(int idx, float x, float y, float z);
	void SetScale(int idx, float x, float y, float z);
	void SetActive(int idx, bool bActive);

	void Move(int idx, float x, float y, float z);
	void Rotate(int idx, float x, float y, float z);
	void Scale(int idx, float x, float y, float z);

	// ÁÂÇ¥°è º¯È­
	glm::mat4 TransformModel(int idx);


	void Update(float elapsedTime);
	void Render(class Renderer*);

	vector<Object*>& GetObjectList() { return m_ObjectList; }

public:
	vector<Object*>	m_ObjectList;
	Player* m_player;
	CameraController* m_cameraController;


};

