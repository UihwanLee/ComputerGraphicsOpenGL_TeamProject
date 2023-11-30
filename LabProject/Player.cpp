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




