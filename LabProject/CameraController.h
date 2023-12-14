#pragma once
#include "KeyBoard.h"
#include "Camera.h"
#include "Light.h"
#include "Types.h"

class CameraController
{
public:

	CameraController();
	~CameraController();

	void Init(vec3 move, vec3 turn);
	void Intersect(float elapsedTime, bool key_w, bool key_s, bool key_a, bool key_d);
	void KeyDown(unsigned char key);
	void KeyUp(unsigned char key);

	void MouseDown(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void Update(float elapsedTime,
		bool& key_w, bool& key_s, bool& key_a, bool& key_d);

public:
	mat4 GetViewMatrix();
	vec3 GetCameraFront();
	vec3 GetCameraPosition();
	Light* GetLight();
	Camera* GetCamera();
	KeyBoard* GetKeyBoard();

	void SetView();
	void SetMoveSpeed(float speed);

private:
	Camera* m_camera;
	KeyBoard* m_keyboard;
	Light* m_light;
	float move_speed = 30.f;

	bool mMouseControl;
	OBB cameraOBB;

public:
	// =============================================
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

	bool IsMouseDown();
	bool IsMouseControl();
	bool IsMouseUp();


	void Update(float elapsedTime);

	bool		mMouseDown;
	bool		mMouseUp;
};