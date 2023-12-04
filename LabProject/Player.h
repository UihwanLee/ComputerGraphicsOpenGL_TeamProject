#pragma once

#include "pch.h"
#include "Object.h"
#include "CameraController.h"

class Player : public Object
{
private:
	bool				m_isMove;

	GLuint				m_shaderProgramID = 0;
	CameraController*	m_cameraController;

public:
	Player(GLuint shaderProgramID, CameraController* cameracontroller, vec3 scale);
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

	void DrawPlayerLight();
};

