#pragma once
#include "KeyBoard.h"
#include "Camera.h"

class CameraController
{
public:
	static CameraController* GetInstance()
	{
		static CameraController s_Insatance;
		return &s_Insatance;
	}
	void Init(Camera* camera, KeyBoard* keyboard);
	~CameraController();


	void MouseDown(int button);
	void MouseMove();
	void Update(float elapsedTime);

private:
	Camera* m_camera;
	KeyBoard* m_keyboard;
	bool mMouseControl;
};