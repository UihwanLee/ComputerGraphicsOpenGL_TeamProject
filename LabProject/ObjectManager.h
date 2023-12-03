#include "pch.h"
#include "Object.h"

#pragma once
class ObjectManager
{
public:
	vector<Object*>	m_ObjectList;
	GLuint			m_shaderProgramID = 0;

public:
	ObjectManager(GLuint shaderProgramID);
	~ObjectManager();

	int GetRandomIntValue(GLfloat min, GLfloat max);
	GLfloat GetRandomFloatValue(GLfloat min, GLfloat max);

	void CreateFigure(Object* gameObject, highp_vec3 color);
	void CreateCube(int* idx, highp_vec3 color, ObjectType type);
	void CreateSqhere(int* idx, highp_vec3 color, ObjectType type);

	void SetPosition(int idx, float x, float y, float z);
	void SetRotate(int idx, float x, float y, float z);
	void SetScale(int idx, float x, float y, float z);
	void SetActive(int idx, bool bActive);

	void Move(int idx, float x, float y, float z);
	void Rotate(int idx, float x, float y, float z);
	void Scale(int idx, float x, float y, float z);

	// ��ǥ�� ��ȭ
	glm::mat4 TransformModel(int idx);

};

