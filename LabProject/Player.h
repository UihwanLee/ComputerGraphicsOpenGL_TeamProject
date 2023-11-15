#include "pch.h"

#pragma once
class Player
{
private:
	GLuint			m_shaderProgramID = 0;

	// ���콺 �巡�׿� ���� ī�޶� ����
	vec3			m_CameraPos;
	vec3			m_AT;

	// Player Movement

public:
	Player(GLuint shaderProgramID);
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

private:
	// ��ȯ ����������
	void DrawView();
	void DrawProjection();
};

