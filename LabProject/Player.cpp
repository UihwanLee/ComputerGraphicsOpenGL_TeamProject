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

Player::Player(GLuint shaderProgramID, CameraController* cameracontroller, vec3 scale)
{
	m_shaderProgramID = shaderProgramID;
	m_cameraController = cameracontroller;
	m_scale = scale;

	m_isMove = true;
}

Player::~Player()
{
	delete this;
}

void Player::Update(float elapsedTime)
{
	if (m_isMove)
	{
		m_cameraController->Update(elapsedTime);
	}
}

void Player::Render(float elapsedTime)
{
	DrawPlayerLight();
}

void Player::DrawPlayerLight()
{
	float distance = 30.f;
	const auto linear_coeff = glm::vec4(
		8.4523112e-05,
		4.4712582e+00,
		-1.8516388e+00,
		3.3955811e+01
	);
	const auto quad_coeff = glm::vec4(
		-7.6103583e-04,
		9.0120201e+00,
		-1.1618500e+01,
		1.0000464e+02
	);

	float kc = 1.0f;
	float d = 1.0f / distance;
	auto dvec = glm::vec4(1.0f, d, d * d, d * d * d);
	float kl = glm::dot(linear_coeff, dvec);
	float kq = glm::dot(quad_coeff, dvec);

	GLuint shaderProgramID = m_shaderProgramID;
	glUseProgram(shaderProgramID);

	//--- uniform 변수 값 받아오기
	const unsigned int pLightPos = glGetUniformLocation(shaderProgramID, "lightPos");
	const unsigned int pLightColor = glGetUniformLocation(shaderProgramID, "lightColor");
	const unsigned int pViewPos = glGetUniformLocation(shaderProgramID, "viewPos");
	const unsigned int atten = glGetUniformLocation(shaderProgramID, "attenuation");
	const unsigned int lightdirection = glGetUniformLocation(shaderProgramID, "lightdirection");
	const unsigned int lightcutoff = glGetUniformLocation(shaderProgramID, "lightcutoff");

	vec3 attenuation = glm::vec3(kc, glm::max(kl, 0.0f), glm::max(kq * kq, 0.0f));
	glUniform3fv(atten, 1, glm::value_ptr(attenuation));

	vec3 lightdirecon = m_cameraController->GetCameraFront();
	glUniform3fv(lightdirection, 1, glm::value_ptr(lightdirecon));

	vec2 cutoff = vec2(5.f, 2.5f);
	glUniform2fv(lightcutoff, 1, glm::value_ptr(vec2(
		glm::cos(glm::radians(cutoff[0])),
		glm::cos(glm::radians(cutoff[0] + cutoff[1]))
	)));

	Light* light = m_cameraController->GetLight();
	glUniform3f(pLightPos, light->GetLightPos().x, light->GetLightPos().y, light->GetLightPos().z);
	glUniform3f(pLightColor, light->GetLightColor().x, light->GetLightColor().y, light->GetLightColor().z);
	glUniform3f(pViewPos, light->GetLightviewPos().x, light->GetLightviewPos().y, light->GetLightviewPos().z);
}




