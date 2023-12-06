#include "pch.h"
#include "CameraController.h"

CameraController::CameraController()
{
	m_camera = new Camera();

	m_keyboard = new KeyBoard();
	m_keyboard->Init();

	m_light = new Light();
}

CameraController::~CameraController()
{
	delete m_camera;
	m_camera = nullptr;

	delete m_keyboard;
	m_keyboard = nullptr;

	delete m_light;
	m_light = nullptr;
}

void CameraController::Init(vec3 move, vec3 turn)
{
	m_camera->MoveTo(move);
	m_camera->TurnTo(turn);

	m_light->SetLightPos(move);
	m_light->SetLightColor(vec3(1.0f, 1.0f, 1.0f));
	m_light->SetView(m_camera->GetPosition());
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
	{
		mMouseDown = true;
		mMouseControl = true;
		mMouseUp = false;
	}
	else if (m_state == KeyState::UP)
	{
		mMouseDown = false;
		mMouseControl = false;
		mMouseUp = true;
	}
}

void CameraController::MouseMove(int x, int y)
{
	m_keyboard->MouseMove(x, y);

	mMouseDown = false;
	mMouseUp = false;

	POINT deltaPos;
	deltaPos.x = m_keyboard->GetMousePos().x - m_keyboard->GetFirstMousePos().x;
	deltaPos.y = m_keyboard->GetMousePos().y - m_keyboard->GetFirstMousePos().y;


	const float cameraRotSpeed = 0.1f;

	if (mMouseControl) {
		m_camera->Yaw(deltaPos.x * cameraRotSpeed);
		m_camera->Pitch(deltaPos.y * cameraRotSpeed);
		m_light->SetLightPos(m_camera->GetPosition());
	}

	m_keyboard->GetFirstMousePos().x = m_keyboard->GetMousePos().x;
	m_keyboard->GetFirstMousePos().y = m_keyboard->GetMousePos().y;
}

void CameraController::Update(float elapsedTime)
{
	m_light->SetLightPos(m_camera->GetPosition());
}

bool CameraController::InputKeyW()
{
	return m_keyboard->Getbutton(KeyType::W);
}

bool CameraController::InputKeyA()
{
	return m_keyboard->Getbutton(KeyType::A);
}

bool CameraController::InputKeyS()
{
	return m_keyboard->Getbutton(KeyType::S);
}

bool CameraController::InputKeyD()
{
	return m_keyboard->Getbutton(KeyType::D);
}

vec3 CameraController::TryMoveFront(float elapsedTime)
{
	return m_camera->TryMove(m_camera->GetForward(), move_speed * elapsedTime);
}

vec3 CameraController::TryMoveBack(float elapsedTime)
{
	return m_camera->TryMove(m_camera->GetForward(), -move_speed * elapsedTime);
}

vec3 CameraController::TryMoveRight(float elapsedTime)
{
	return m_camera->TryMove(m_camera->GetRight(), move_speed * elapsedTime);
}

vec3 CameraController::TryMoveLeft(float elapsedTime)
{
	return m_camera->TryMove(m_camera->GetRight(), -move_speed * elapsedTime);
}

void CameraController::MoveFront(float elapsedTime)
{
	m_camera->Move(m_camera->GetForward(), move_speed * elapsedTime);
}

void CameraController::MoveBack(float elapsedTime)
{
	m_camera->Move(m_camera->GetForward(), -move_speed * elapsedTime);
}

void CameraController::MoveRight(float elapsedTime)
{
	m_camera->Move(m_camera->GetRight(), move_speed * elapsedTime);
}

void CameraController::MoveLeft(float elapsedTime)
{
	m_camera->Move(m_camera->GetRight(), -move_speed * elapsedTime);
}

bool CameraController::IsMouseDown()
{
	return mMouseDown;
}

bool CameraController::IsMouseUp()
{
	return mMouseUp;
}

bool CameraController::IsMouseControl()
{
	return mMouseControl;
}

mat4 CameraController::GetViewMatrix()
{
	return m_camera->GetViewMatrix();
}

mat4 CameraController::GetRotationMatrix()
{
	return m_camera->GetRotationMatrix();
}

vec3 CameraController::GetCameraFront()
{
	return m_camera->GetForward();
}

vec3 CameraController::GetPosition()
{
	return m_camera->GetPosition();
}

vec3 CameraController::GetRotate()
{
	return m_camera->GetRotate();
}

void CameraController::SetView()
{

}

Light* CameraController::GetLight()
{
	m_light->SetView(m_camera->GetPosition());
	return m_light;
}

