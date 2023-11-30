#include "pch.h"
#include "Scene02.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Scene02::Scene02(GLuint shaderProgramID)
{
	m_shaderProgramID = shaderProgramID;
}

Scene02::~Scene02()
{
	delete m_Player;
	delete m_ObjectManager;
}

void Scene02::Init()
{
	// VBO Gen
	glGenBuffers(3, VBO);
	glGenTextures(1, &texture);

	// ī�޶� �ʱ�ȭ
	camera.MoveTo(vec3(0.f, 0.0f, 5.f));	// ī�޶� ��ġ
	camera.TurnTo(vec3(0.f, 0.f, 0.f)); // ī�޶� ����
	CameraController::GetInstance()->Init(&camera, KeyBoard::GetInstance());

	// �÷��̾� ����
	m_Player = new Player();

	// ������Ʈ ����
	m_ObjectManager = new ObjectManager();

	m_ObjectManager->CreateCube(highp_vec3(1.0f, 1.0f, 1.0f));
	m_ObjectManager->SetScale(0, 10.0f, 0.2f, 10.0f);
	m_ObjectManager->SetPosition(0, 0.0f, -1.5f, 0.0f);

	m_ObjectManager->CreateCube(highp_vec3(1.0f, 1.0f, 0.0f));
	m_ObjectManager->SetScale(1, 1.0, 1.0f, 1.0f);
	m_ObjectManager->SetPosition(1, 0.0f, 0.4f, 0.0f);

}

void Scene02::Render(float elapsedTime)
{
	DrawView();
	DrawProjection();
	DrawPlayerLight();

	DrawStage2(elapsedTime);
	DrawEndStage(elapsedTime);
}

void Scene02::Update(float elapsedTime)
{
	m_Player->Update(elapsedTime);
}

void Scene02::DrawView()
{
	unsigned int viewLocation = glGetUniformLocation(m_shaderProgramID, "viewTransform");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
}

void Scene02::DrawProjection()
{
	unsigned int projectionLocation = glGetUniformLocation(m_shaderProgramID, "projectionTransform");

	glm::mat4 projection = glm::mat4(1.0f);

	// ���� ����
	float fov = 45.0f; // �þ߰� (Field of View)
	float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // ȭ���� ���� ���� ����
	float zNear = 0.1f; // ����� Ŭ���� ���
	float zFar = 50.0f; // �� Ŭ���� ���
	projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar); //--- ���� ���� ����: (���װ���, ��Ⱦ��, �����Ÿ�, �հŸ�)

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);		// ������ȯ
}

void Scene02::DrawPlayerLight()
{
	unsigned int lightPosLocation = glGetUniformLocation(m_shaderProgramID, "lightPos"); //--- lightPos �� ����: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, m_Player->m_LightPos.x, m_Player->m_LightPos.y, m_Player->m_LightPos.z);
	unsigned int lightColorLocation = glGetUniformLocation(m_shaderProgramID, "lightColor"); //--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, m_Player->m_LightColor.r, m_Player->m_LightColor.g, m_Player->m_LightColor.b);
	unsigned int viewPosLocation = glGetUniformLocation(m_shaderProgramID, "viewPos"); //--- viewPos �� ����: ī�޶� ��ġ
	glUniform3f(viewPosLocation, 0.0f, 0.0f, 0.0f);
}

void Scene02::DrawObject(int DRAW_TYPE, glm::mat4& model, int idx)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, m_ObjectManager->m_ObjectList[idx]->m_vertices.size() * sizeof(glm::vec3), &m_ObjectManager->m_ObjectList[idx]->m_vertices[0], GL_STATIC_DRAW);

	// �𵨺�ȯ
	unsigned int modelLocation = glGetUniformLocation(m_shaderProgramID, "modelTransform");
	m_ObjectManager->m_ObjectList[idx]->m_model = m_ObjectManager->TransformModel(idx);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_ObjectManager->m_ObjectList[idx]->m_model));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, m_ObjectManager->m_ObjectList[idx]->m_normals.size() * sizeof(glm::vec3), &m_ObjectManager->m_ObjectList[idx]->m_normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	unsigned int objColorLocation = glGetUniformLocation(m_shaderProgramID, "objectColor"); //--- object Color�� ���� 
	glUniform3f(objColorLocation, m_ObjectManager->m_ObjectList[idx]->m_colors.r, m_ObjectManager->m_ObjectList[idx]->m_colors.g, m_ObjectManager->m_ObjectList[idx]->m_colors.b);

	// vTexture
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, m_ObjectManager->m_ObjectList[idx]->m_uvs.size() * sizeof(glm::vec2), &m_ObjectManager->m_ObjectList[idx]->m_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	// Texture
	int widthImage, heightImage, numberOfChannel;
	// stbi_set_flip_vertically_on_load(true); //--- �̹����� �Ųٷ� �����ٸ� �߰�
	unsigned char* data = stbi_load("wall_texture.jfif", &widthImage, &heightImage, &numberOfChannel, 0);

	unsigned int objTextureLocation = glGetUniformLocation(m_shaderProgramID, "outTexture");
	glUniform1i(objTextureLocation, 0);

	glActiveTexture(GL_TEXTURE0); //--- ���� 0�� Ȱ��ȭ
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDrawArrays(DRAW_TYPE, 0, m_ObjectManager->m_ObjectList[idx]->m_vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	stbi_image_free(data);
}

void Scene02::DrawEndStage(float elapsedTime)
{
}

void Scene02::DrawStage2(float elapsedTime)
{
	for (int i = 0; i < m_ObjectManager->m_ObjectList.size(); i++)
	{
		if (m_ObjectManager->m_ObjectList[i]->m_bActive)
		{
			DrawObject(m_ObjectManager->m_ObjectList[i]->m_DRAW_TYPE, m_ObjectManager->m_ObjectList[i]->m_model, i);
		}
	}
}
