#pragma once

#include "KeyBoard.h"
#include "Camera.h"
#include "Light.h"

class CameraController
{
public:

	CameraController();
	~CameraController();

	void Init(vec3 move, vec3 turn);

	void KeyDown(unsigned char key);
	void KeyUp(unsigned char key);

	void MouseDown(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void Update(float elapsedTime);

public:
	bool InputKeyW();
	bool InputKeyA();
	bool InputKeyS();
	bool InputKeyD();

	vec3 TryMoveFront(float elapsedTime);
	vec3 TryMoveBack(float elapsedTime);
	vec3 TryMoveRight(float elapsedTime);
	vec3 TryMoveLeft(float elapsedTime);

	void MoveFront(float elapsedTime);
	void MoveBack(float elapsedTime);
	void MoveRight(float elapsedTime);
	void MoveLeft(float elapsedTime);

public:
	mat4 GetViewMatrix();
	vec3 GetCameraFront();

	vec3 GetPosition();

	void SetView();
	Light* GetLight();

private:
	float		move_speed = 10.f;

	Camera*		m_camera;
	KeyBoard*	m_keyboard;
	Light*		m_light;

	bool mMouseControl;
};