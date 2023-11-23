#include "pch.h"
#include "CameraController.h"

void CameraController::Init(Camera* camera, KeyBoard* keyboard)
{
	m_camera = camera;
	m_keyboard = keyboard;

}


CameraController::~CameraController()
{
}

void CameraController::MouseDown(int button)
{
	KeyState& m_state = m_keyboard->GetState()[button];

	if (m_state == KeyState::PRESS)
		mMouseControl = true;
	else if (m_state == KeyState::UP)
		mMouseControl = false;
}

void CameraController::MouseMove()
{
	POINT deltaPos;
	deltaPos.x = m_keyboard->GetMousePos().x - m_keyboard->GetFirstMousePos().x;
	deltaPos.y = m_keyboard->GetMousePos().y - m_keyboard->GetFirstMousePos().y;


	const float cameraRotSpeed = 0.05f;

	if (mMouseControl) {
		m_camera->Yaw(deltaPos.x * cameraRotSpeed);
		m_camera->Pitch(deltaPos.y * cameraRotSpeed);
	}

	m_keyboard->GetFirstMousePos().x = m_keyboard->GetMousePos().x;
	m_keyboard->GetFirstMousePos().y = m_keyboard->GetMousePos().y;
}

void CameraController::Update(float elapsedTime)
{
	float move_speed = 10.f;

	if (m_keyboard->Getbutton(KeyType::A)) {
		m_camera->Move(m_camera->GetRight(), -move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::D)) {
		m_camera->Move(m_camera->GetRight(), move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::W)) {
		m_camera->Move(m_camera->GetForward(), move_speed * elapsedTime);
	}
	if (m_keyboard->Getbutton(KeyType::S)) {
		m_camera->Move(m_camera->GetForward(), -move_speed * elapsedTime);
	}

}
