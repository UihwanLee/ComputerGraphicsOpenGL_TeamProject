#include "pch.h"
#include "Object.h"

#pragma once
class Player : public Object
{
public:
	// ���콺 �巡�׿� ���� ī�޶� ����
	vec3			m_cameraPos;
	vec3			m_cameraFront;
	vec3			m_cameraUp;
	vec3			m_AT;

	vec3			m_LightPos;
	highp_vec3		m_LightColor;

public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);
};

