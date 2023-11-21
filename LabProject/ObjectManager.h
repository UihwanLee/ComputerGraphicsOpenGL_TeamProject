#include "pch.h"
#include "Object.h"

#pragma once
class ObjectManager
{
public:
	vector<Object*>	m_ObjectList;

public:
	ObjectManager();
	~ObjectManager();

	int GetRandomIntValue(GLfloat min, GLfloat max);
	GLfloat GetRandomFloatValue(GLfloat min, GLfloat max);

	void CreateFigure(Object* gameObject, highp_vec3 color);
	void CreateCube(highp_vec3 color);
	void CreateSqhere(highp_vec3 color);

	void SetPosition(int idx, float x, float y, float z);
	void SetRotate(int idx, float x, float y, float z);
	void SetScale(int idx, float x, float y, float z);
	void SetActive(int idx, bool bActive);

	void Move(int idx, float x, float y, float z);
	void Rotate(int idx, float x, float y, float z);
	void Scale(int idx, float x, float y, float z);

	// ÁÂÇ¥°è º¯È­
	glm::mat4 TransformModel(int idx);
};

