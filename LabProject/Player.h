#include "pch.h"

#pragma once
class Player
{
private:
	GLuint			m_shaderProgramID = 0;

	// 마우스 드래그에 따른 카메라 조작
	vec3			m_CameraPos;
	vec3			m_AT;

	// Player Movement

public:
	Player(GLuint shaderProgramID);
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

private:
	// 변환 파이프라인
	void DrawView();
	void DrawProjection();
};

