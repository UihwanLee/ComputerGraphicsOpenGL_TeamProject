#include "pch.h"
#include "Object.h"
#include "CameraController.h"

#pragma once
class Player : public Object
{
public:
	Player(GLuint shaderProgramID, CameraController*);
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

	void DrawPlayerLight();

private:
	GLuint				m_shaderProgramID = 0;
	CameraController*	m_cameraController;
};

