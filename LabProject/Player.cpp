#include "pch.h"
#include "Player.h"

vec3 cameraPos = glm::vec3(0.0f, 0.2f, 0.0f);
vec3 cameraFront = glm::vec3(0.0f, 0.0f, -2.0f);
vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.05f;

bool g_left_button = false;

float lastX = 0.0f;
float lastY = 0.0f;

float f_yaw = 0.0f;
float f_pitch = 0.0f;

Player::Player()
{
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	m_cameraUp = glm::vec3(0.0f, 0.0f, 0.0f);
	m_AT = glm::vec3(0.0f, 0.0f, 0.0f);

	m_position.x = 0.0f; m_position.y = 0.0f; m_position.z = 0.0f;
	m_rotate.x = 0.0f; m_rotate.y = 0.0f; m_rotate.z = 0.0f;
	m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f;

	m_model = glm::mat4(1.0f);
	m_bActive = true;

	m_LightPos.x = 0.0f; m_LightPos.y = 0.0f; m_LightPos.z = 0.0f;
	m_LightColor.r = 1.0f; m_LightColor.g = 1.0f; m_LightColor.b = 1.0f;
}

Player::~Player()
{
	delete this;
}

void Player::Update(float elapsedTime)
{

}

void Player::Render(float elapsedTime)
{
	
}




