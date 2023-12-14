#include "pch.h"
#include "CameraController.h"

CameraController::CameraController()
{
	m_camera = new Camera();
	m_keyboard = new KeyBoard();
	m_keyboard->Init();
	m_light = new Light();

	cameraOBB.center = m_camera->GetPosition();;
	cameraOBB.halfSize = glm::vec3(0.5, 0.5, 0.5f);  // 예시 크기
	cameraOBB.orientation = glm::mat4(1.0f);  // 회전 없음
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

	m_light->SetLightPos(move);
	m_light->SetLightColor(vec3(1.0f, 1.0f, 1.0f));
	m_light->SetView(m_camera->GetPosition());
}

void CameraController::Intersect(float elapsedTime, bool key_w, bool key_s, bool key_a, bool key_d)
{

	if (key_w) {
		m_camera->Move(m_camera->GetForward(), -move_speed * elapsedTime);
	}
	if (key_s) {
		m_camera->Move(m_camera->GetForward(), move_speed * elapsedTime);
	}
	if (key_a) {
		m_camera->Move(m_camera->GetRight(), move_speed * elapsedTime);
	}
	if (key_d) {
		m_camera->Move(m_camera->GetRight(), -move_speed * elapsedTime);
	}
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

	if (m_state == KeyState::PRESS) {
		mMouseDown = true;
		mMouseControl = true;
		mMouseUp = false;
	}
	else if (m_state == KeyState::UP) {
		mMouseDown = false;
		mMouseControl = false;
		mMouseUp = true;
	}
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
		m_light->SetLightPos(m_camera->GetPosition());
	}

	m_keyboard->GetFirstMousePos().x = m_keyboard->GetMousePos().x;
	m_keyboard->GetFirstMousePos().y = m_keyboard->GetMousePos().y;
}

void CameraController::Update(float elapsedTime, bool& key_w, bool& key_s, bool& key_a, bool& key_d)
{

	if (m_keyboard->Getbutton(KeyType::A)) {
		m_camera->Move(m_camera->GetRight(), -move_speed * elapsedTime);
		key_a = true;
	}
	if (m_keyboard->Getbutton(KeyType::D)) {
		m_camera->Move(m_camera->GetRight(), move_speed * elapsedTime);
		key_d = true;
	}
	if (m_keyboard->Getbutton(KeyType::W)) {
		m_camera->Move(m_camera->GetForward(), move_speed * elapsedTime);
		key_w = true;
	}
	if (m_keyboard->Getbutton(KeyType::S)) {
		m_camera->Move(m_camera->GetForward(), -move_speed * elapsedTime);
		key_s = true;
	}
	vec3 p = m_camera->GetPosition();

	m_light->SetLightPos(m_camera->GetPosition());
}

void CameraController::SetView()
{

}

void CameraController::SetMoveSpeed(float speed)
{
	move_speed = speed;
}

Light* CameraController::GetLight()
{
	m_light->SetView(m_camera->GetPosition());
	return m_light;
}

Camera* CameraController::GetCamera()
{
	return m_camera;
}

KeyBoard* CameraController::GetKeyBoard()
{
	return m_keyboard;
}

mat4 CameraController::GetViewMatrix()
{
	return m_camera->GetViewMatrix();
}

vec3 CameraController::GetCameraFront()
{
	return m_camera->GetForward();
}

vec3 CameraController::GetCameraPosition()
{
	return m_camera->GetPosition();
}


// ====================================

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

void CameraController::Update(float elapsedTime)
{
	m_light->SetLightPos(m_camera->GetPosition());
}

bool CameraController::IsMouseControl()
{
	return mMouseControl;
}