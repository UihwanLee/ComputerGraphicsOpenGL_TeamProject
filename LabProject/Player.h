#include "pch.h"
#include "Object.h"

#pragma once
class Player : public Object
{
public:
	// 마우스 드래그에 따른 카메라 조작
	vec3			m_cameraPos;
	vec3			m_cameraFront;
	vec3			m_cameraUp;
	vec3			m_AT;

	vec3			m_LightPos;
	highp_vec3		m_LightColor;

	// Player Movement
	float					m_mass;
	vec3					m_vel;
	vec3					m_acc;
	vec3					m_force;

public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

	// Player Movement
	void SetVel(float x, float y, float z);
	void SetAcc(float x, float y, float z);
	void SetForce(float x, float y, float z);

	void AddForce(float x, float y, float z, float elapsedTime);

	void CreatPlayerMesh();

	// 좌표계 변화
	glm::mat4 TransformModel();
};

