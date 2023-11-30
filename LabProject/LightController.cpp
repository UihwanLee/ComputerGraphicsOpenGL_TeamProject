#include "pch.h"
#include "LightController.h"

void LightController::Init(Light* light, KeyBoard* keyboard)
{
	m_light = light;
	m_keyboard = keyboard;
}

LightController::~LightController()
{
}

void LightController::MouseDown(int button)
{
	KeyState& m_state = m_keyboard->GetState()[button];

	if (m_state == KeyState::PRESS)
		mMouseControl = true;
	else if (m_state == KeyState::UP)
		mMouseControl = false;
}

void LightController::MouseMove()
{
	POINT deltaPos;
	deltaPos.x = m_keyboard->GetMousePos().x - m_keyboard->GetFirstMousePos().x;
	deltaPos.y = m_keyboard->GetMousePos().y - m_keyboard->GetFirstMousePos().y;

	const float cameraRotSpeed = 0.05f;

	if (mMouseControl) {
		m_light->Yaw(deltaPos.x * cameraRotSpeed);
		m_light->Pitch(deltaPos.y * cameraRotSpeed);
	}

	m_keyboard->GetFirstMousePos().x = m_keyboard->GetMousePos().x;
	m_keyboard->GetFirstMousePos().y = m_keyboard->GetMousePos().y;
}

void LightController::Update(float elapsedTime)
{
	float move_speed = 10.f;

	if (m_keyboard->Getbutton(KeyType::A)) {
		m_light->Move(m_light->GetRight(), -move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::D)) {
		m_light->Move(m_light->GetRight(), move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::W)) {
		m_light->Move(m_light->GetForward(), move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::S)) {
		m_light->Move(m_light->GetForward(), -move_speed * elapsedTime);
	}
}
