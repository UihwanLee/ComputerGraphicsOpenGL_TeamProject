#include "pch.h"
#include "Player.h"

Player::Player()
{
	m_CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_AT = glm::vec3(0.0f, 0.0f, 0.0f);

	m_position.x = 0.0f; m_position.y = 0.0f; m_position.z = 0.0f;
	m_rotate.x = 0.0f; m_rotate.y = 0.0f; m_rotate.z = 0.0f;
	m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f;

	m_model = glm::mat4(1.0f);
	m_bActive = true;

	m_LightPos.x = 0.0f; m_LightPos.y = 0.0f; m_LightPos.z = 0.0f;
	m_LightColor.r = 1.0f; m_LightColor.g = 1.0f; m_LightColor.b = 1.0f;

	CreatPlayerMesh();
}

Player::~Player()
{
	delete this;
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




