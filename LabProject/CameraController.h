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
	mat4 GetViewMatrix();
	vec3 GetCameraFront();

	void SetView();
	Light* GetLight();

private:
	Camera* m_camera;
	KeyBoard* m_keyboard;
	Light* m_light;

	bool mMouseControl;
};