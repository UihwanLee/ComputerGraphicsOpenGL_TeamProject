#include "pch.h"
#include "CameraController.h"

CameraController::CameraController()
{
	m_camera = new Camera();

	m_keyboard = new KeyBoard();
	m_keyboard->Init();
}

CameraController::~CameraController()
{
	delete m_camera;
	m_camera = nullptr;

	delete m_keyboard;
	m_keyboard = nullptr;
}

void CameraController::Init(vec3 move, vec3 turn)
{
	m_camera->MoveTo(move);
	m_camera->TurnTo(turn);
}

void CameraController::KeyDown(unsigned char key)
{
	m_keyboard->KeyDown(key);
}

void CameraController::KeyUp(unsigned char key)
{
	m_keyboard->KeyUp(key);
}

void CameraController::MouseDown(int button, int state, int x, int y)
{
	m_keyboard->MouseDown(button, state, x, y);
	KeyState& m_state = m_keyboard->GetState()[button];

	if (m_state == KeyState::PRESS)
		mMouseControl = true;
	else if (m_state == KeyState::UP)
		mMouseControl = false;
}

void CameraController::MouseMove(int x, int y)
{
	m_keyboard->MouseMove(x, y);

	POINT deltaPos;
	deltaPos.x = m_keyboard->GetMousePos().x - m_keyboard->GetFirstMousePos().x;
	deltaPos.y = m_keyboard->GetMousePos().y - m_keyboard->GetFirstMousePos().y;


	const float cameraRotSpeed = 0.1f;

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

mat4 CameraController::GetViewMatrix()
{
	return m_camera->GetViewMatrix();
}

vec3 CameraController::GetCameraFront()
{
	return m_camera->GetForward();
}
