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

	m_mass = 1.0f;
	m_vel.x = 0.0f; m_vel.y = 0.0f; m_vel.z = 0.0f;
	m_acc.x = 0.0f; m_acc.y = 0.0f; m_acc.z = 0.0f;
	m_force.x = 0.0f; m_force.y = 0.0f; m_force.z = 0.0f;

	CreatPlayerMesh();
}

Player::~Player()
{
	delete this;
}

GLvoid KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		//cameraPos.z -= 1.0f;
		cameraPos += cameraSpeed * cameraFront;
		break;
	case 'a':
		//cameraPos.x -= 1.0f;
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;
	case 's':
		// cameraPos.z += 1.0f;
		cameraPos -= cameraSpeed * cameraFront;
		break;
	case 'd':
		// cameraPos.x += 1.0f;
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// 마우스 클릭 ...

		float start_x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f; // x 끝점
		float start_y = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT); // y 끝점

		// curAngle = GetClickPos(x, 0.0f, 800.0f, -60.0f, 60.0f);

		g_left_button = true;
	}

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (g_left_button)
	{
		float xoffset = x - lastX;
		float yoffset = lastY - y;
		lastX = x;
		lastY = y;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		f_yaw += xoffset;
		f_pitch += yoffset;

		if (f_yaw > 89.0f)
			f_yaw = 89.0f;
		if (f_pitch < -89.0f)
			f_pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(f_yaw)) * cos(glm::radians(f_pitch));
		direction.y = sin(glm::radians(f_pitch));
		direction.z = sin(glm::radians(f_yaw)) * cos(glm::radians(f_pitch));
		cameraFront = glm::normalize(direction);
	}

	glutPostRedisplay();
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

	// 카메라
	m_cameraPos.x = cameraPos.x;
	m_cameraPos.y = cameraPos.y;
	m_cameraPos.z = cameraPos.z;

	m_cameraFront.x = cameraFront.x;
	m_cameraFront.y = cameraFront.y;
	m_cameraFront.z = cameraFront.z;

	m_cameraUp.x = m_cameraUp.x;
	m_cameraUp.y = m_cameraUp.y;
	m_cameraUp.z = m_cameraUp.z;

	// 속도 계산
	float t = elapsedTime;
	float tt = t * t;

	//accel
	//m_accX = m_forceX / m_mass;
	//m_accY = m_forceY / m_mass;
	//m_accZ = m_forceZ / m_mass;

	//vel
	//m_velX = m_velX + m_accX * t;
	//m_velY = m_velY + m_accY * t;
	//m_velZ = m_velZ + m_accZ * t;

	//pos
	//m_posX = m_posX + m_velX * t + 0.5f * m_accX * tt;
	//m_posY = m_posY + m_velY * t + 0.5f * m_accY * tt;
	//m_posZ = m_posZ + m_velZ * t + 0.5f * m_accZ * tt;

	//m_velX.... apply friction
	//cal normal force
	float normalForce = m_mass * GRAVITY;

	float frictionCoef = 50.f;

	float friction = frictionCoef * normalForce;

	float frictionDirX = -m_vel.x;
	float frictionDirY = -m_vel.z;

	float mag = sqrtf(frictionDirX * frictionDirX + frictionDirY * frictionDirY);

	if (mag > FLT_EPSILON)
	{
		frictionDirX = frictionDirX / mag;
		frictionDirY = frictionDirY / mag;

		float frictionForceX = frictionDirX * friction;
		float frictionForceY = frictionDirY * friction;

		float frictionAccX = frictionForceX / m_mass;
		float frictionAccY = frictionForceY / m_mass;

		float resultVelX = m_vel.x + frictionAccX * elapsedTime;
		float resultVelY = m_vel.z + frictionAccY * elapsedTime;
		float resultVelZ = m_vel.y;

		if (resultVelX * m_vel.x < 0.f)
		{
			m_vel.x = 0.f;
		}
		else
		{
			m_vel.x = resultVelX;
		}

		if (resultVelY * m_vel.z < 0.f)
		{
			m_vel.z = 0.f;
		}
		else
		{
			m_vel.z = resultVelY;
		}

		if (resultVelZ * m_vel.y < 0.f)
		{
			m_vel.y = 0.f;
		}
		else
		{
			m_vel.y = resultVelZ;
		}
	}

	m_position.x = m_position.x + m_vel.x * t;
	m_position.y = m_position.y + m_vel.y * t;
	m_position.z = m_position.z + m_vel.z * t;

	if (m_position.y < 0.0f)
	{
		m_position.y = 0.0f;
	}
}

void Player::Render(float elapsedTime)
{
	
}

void Player::SetVel(float x, float y, float z)
{
	m_vel.x = x;
	m_vel.y = y;
	m_vel.z = z;
}

void Player::SetAcc(float x, float y, float z)
{
	m_acc.x = x;
	m_acc.y = y;
	m_acc.z = z;
}

void Player::SetForce(float x, float y, float z)
{
	m_force.x = x;
	m_force.y = y;
	m_force.z = z;
}

void Player::AddForce(float x, float y, float z, float elapsedTime)
{
	float accX = x / m_mass;
	float accY = y / m_mass;
	float accZ = z / m_mass;

	m_vel.x = m_vel.x + accX * elapsedTime;
	m_vel.y = m_vel.y + accY * elapsedTime;
	m_vel.z = m_vel.z + accZ * elapsedTime;
}

void Player::CreatPlayerMesh()
{
	LoadMeshInfoFromFile("cube.txt");

	// vertexs
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		m_vertices.push_back(vertex);
	}

	// uvs
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		m_uvs.push_back(uv);
	}

	// normals
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		m_normals.push_back(normal);
	}

	m_colors.r = 0.0f; m_colors.g = 0.0f; m_colors.b = 1.0f;

	m_DRAW_TYPE = GL_TRIANGLES;

	m_bActive = true;
}

glm::mat4 Player::TransformModel()
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 move = glm::mat4(1.0f);

	model = glm::mat4(1.0f);

	// 기본 Transform
	model = glm::scale(model, glm::vec3(m_scale.x, m_scale.y, m_scale.z));
	model = glm::rotate(model, glm::radians(m_rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));

	return model;
}




