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
	//DrawStartStage(elapsedTime);
	DrawStage1(elapsedTime);
}

void Scene01::Update(float elapsedTime)
{
}

void Scene01::DrawStartStage(float elapsedTime)
{
	GLfloat CubeColor[24] = {
		   1.0f, 0.0f, 0.0f, // 0
		   0.0f, 1.0f, 0.0f, // 1
		   0.0f, 0.0f, 1.0f, // 2
		   1.0f, 1.0f, 0.0f, // 3
		   0.0f, 1.0f, 1.0f, // 4
		   1.0f, 0.0f, 1.0f, // 5
		   0.0f, 0.0f, 0.0f, // 6
		   1.0f, 1.0f, 1.0f  // 7
	};

	glUseProgram(m_shaderProgramID);
	glm::mat4 m_model = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(m_shaderProgramID, "modelTransform");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

	// layout 0 -> vPos : VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(sizeof(GLfloat) * 0));

	// layout 1 -> vColor : VBO[1]
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vTest.size() * sizeof(glm::vec3), CubeColor, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

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
		1,0,2, 1,2,3,    // 앞
		4,0,6, 0,2,6,    // 왼
		5,1,3, 5,3,7,    // 오
		5,4,7, 4,6,7,    // 뒤
		5,4,0, 5,0,1,    // 위
		3,6,2, 3,7,6     // 아
	};

	for (const int& i : cubeIndex)
	{
		vTest.push_back(Cube[i]);
	}

	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vTest.size() * sizeof(glm::vec3), vTest.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vTest.size() * sizeof(glm::vec3), CubeColor, GL_STATIC_DRAW);
}
