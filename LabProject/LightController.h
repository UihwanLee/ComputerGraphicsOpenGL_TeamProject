#pragma once
#include "KeyBoard.h"
#include "Light.h"

class LightController
{
public:
	static LightController* GetInstance()
	{
		static LightController s_Insatance;
		return &s_Insatance;
	}
	void Init(Light* light, KeyBoard* keyboard);
	~LightController();


	void MouseDown(int button);
	void MouseMove();
	void Update(float elapsedTime);

private:
	Light* m_light;
	KeyBoard* m_keyboard;
	bool mMouseControl;
};

