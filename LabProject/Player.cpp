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
	// ���콺
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	// Ű����
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

	glm::vec3 cameraPos = glm::vec3(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(m_AT.x, m_AT.y, m_AT.z); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);

	//view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);		// �亯ȯ
}

void Player::DrawProjection()
{
	unsigned int projectionLocation = glGetUniformLocation(m_shaderProgramID, "projectionTransform");

	glm::mat4 projection = glm::mat4(1.0f);

	// ���� ����
	float left = -1.0f;
	float right = 1.0f;
	float bottom = -1.0f;
	float top = 1.0f;
	float zNear = -10.0f;
	float zFar = 10.0f;
	projection = glm::ortho(left, right, bottom, top, zNear, zFar);

	// ���� ����
	//float fov = 45.0f; // �þ߰� (Field of View)
	//float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // ȭ���� ���� ���� ����
	//float zNear = 0.1f; // ����� Ŭ���� ���
	//float zFar = 50.0f; // �� Ŭ���� ���
	//projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar); //--- ���� ���� ����: (���װ���, ��Ⱦ��, �����Ÿ�, �հŸ�)

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);		// ������ȯ
}
