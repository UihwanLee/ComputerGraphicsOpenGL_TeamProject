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

public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);
};

