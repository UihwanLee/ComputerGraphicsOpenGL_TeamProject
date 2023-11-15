#include "pch.h"
#include "Player.h"

Player::Player(GLuint shaderProgramID)
{
	m_shaderProgramID = shaderProgramID;

	m_CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_AT = glm::vec3(0.0f, 0.0f, 0.0f);
}

Player::~Player()
{
}

GLvoid KeyboardDown(unsigned char key, int x, int y)
{

}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{

}

GLvoid SpecialDownKey(int key, int x, int y)
{

}

GLvoid SpecialUpKey(int key, int x, int y)
{

}

void Mouse(int button, int state, int x, int y)
{

}

void Motion(int x, int y)
{

}

void Player::Update(float elapsedTime)
{
	// 마우스
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	// 키보드
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

	glutSpecialFunc(SpecialDownKey);
	glutSpecialUpFunc(SpecialUpKey);
}

void Player::Render(float elapsedTime)
{
	DrawView();
	DrawProjection();
}

void Player::DrawView()
{
	unsigned int viewLocation = glGetUniformLocation(m_shaderProgramID, "viewTransform");

	glm::vec3 cameraPos = glm::vec3(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(m_AT.x, m_AT.y, m_AT.z); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);

	//view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);		// 뷰변환
}

void Player::DrawProjection()
{
	unsigned int projectionLocation = glGetUniformLocation(m_shaderProgramID, "projectionTransform");

	glm::mat4 projection = glm::mat4(1.0f);

	// 직교 투영
	float left = -1.0f;
	float right = 1.0f;
	float bottom = -1.0f;
	float top = 1.0f;
	float zNear = -10.0f;
	float zFar = 10.0f;
	projection = glm::ortho(left, right, bottom, top, zNear, zFar);

	// 원근 투영
	//float fov = 45.0f; // 시야각 (Field of View)
	//float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // 화면의 가로 세로 비율
	//float zNear = 0.1f; // 가까운 클리핑 평면
	//float zFar = 50.0f; // 먼 클리핑 평면
	//projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar); //--- 투영 공간 설정: (뷰잉각도, 종횡비, 가까운거리, 먼거리)

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);		// 투영변환
}
