#include "pch.h"
#include "Scene01.h"

Scene01::Scene01(GLuint shaderProgramID)
{
	m_shaderProgramID = shaderProgramID;
}

Scene01::~Scene01()
{
}

void Scene01::Init()
{
	CreateVertexBufferObjectBox();
}

void Scene01::Render(float elapsedTime)
{
	DrawStartStage(elapsedTime);
	DrawStage1(elapsedTime);
}

void Scene01::Update(float elapsedTime)
{
}

void Scene01::DrawStartStage(float elapsedTime)
{
	glUseProgram(m_shaderProgramID);
	glm::mat4 m_model = glm::mat4(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));


	GLint AttributePosition = glGetAttribLocation(m_shaderProgramID, "in_Position");
	glEnableVertexAttribArray(AttributePosition);
	glUniform3f(glGetUniformLocation(m_shaderProgramID, "in_Color"), 0.f, 1.f, 0.f);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Test);
	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(sizeof(GLfloat) * 0));

	glDrawArrays(GL_TRIANGLES, 0, vTest.size());
}

void Scene01::DrawStage1(float elapsedTime)
{
}

void Scene01::CreateVertexBufferObjectBox()
{
	float size{ 0.5f };

	glm::vec3 Cube[] = {
		{-size, +size, +size}, // 0
		{+size, +size, +size}, // 1
		{-size, -size, +size}, // 2
		{+size, -size, +size}, // 3
		{-size, +size, -size}, // 4
		{+size, +size, -size}, // 5
		{-size, -size, -size}, // 6
		{+size, -size, -size}, // 7
	};

	glm::vec3 CubeColor[] = {
		{1.0f, 0.0f, 0.0f}, // 0
		{0.0f, 1.0f, 0.0f}, // 1
		{0.0f, 0.0f, 1.0f}, // 2
		{1.0f, 1.0f, 0.0f}, // 3
		{0.0f, 1.0f, 1.0f}, // 4
		{1.0f, 0.0f, 1.0f}, // 5
		{0.0f, 0.0f, 0.0f}, // 6
		{1.0f, 1.0f, 1.0f}  // 7
	};

	const int cubeIndex[] =
	{
		1,0,2, 1,2,3,    // ��
		4,0,6, 0,2,6,    // ��
		5,1,3, 5,3,7,    // ��
		5,4,7, 4,6,7,    // ��
		5,4,0, 5,0,1,    // ��
		3,6,2, 3,7,6     // ��
	};

	for (const int& i : cubeIndex)
	{
		vTest.push_back(Cube[i]);
	}

	glGenBuffers(1, &VBO_Test);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Test);
	glBufferData(GL_ARRAY_BUFFER, vTest.size() * sizeof(glm::vec3), vTest.data(), GL_STATIC_DRAW);
}
