#pragma once
#include "pch.h"
#include "Object.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float elapsedTime, class Renderer* renderer, class CameraController* cameracontroller, vec3, vec3);
	void Render(class Renderer* renderer, class CameraController* cameracontroller);


	// ======================
private:

	bool				m_isMove;

	GLuint				m_shaderProgramID = 0;
	CameraController* m_cameraController;

public:
	Player(GLuint shaderProgramID, CameraController* cameracontroller, vec3 scale);

	void Update(float elapsedTime);
	void Render(float elapsedTime);

	void DrawPlayerLight();

	vec3 m_scale;

};

