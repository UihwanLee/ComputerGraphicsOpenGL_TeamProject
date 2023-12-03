#include "pch.h"
#include "Scene02.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

vec3 pointLightPositions[5] = {
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(4.0f,  0.0f, 0.0f),
		glm::vec3(-4.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 7.0f),
		glm::vec3(0.0f,  0.0f, 15.0f),
};

Scene02::Scene02(CameraController* cameracontroller)
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_ObjectManager = new ObjectManager(m_Renderer->GetShaderProgramID());

	m_shaderProgramID = m_Renderer->GetShaderProgramID();

	m_cameraController = cameracontroller;
	m_cameraController->Init(vec3(0.f, 0.0f, -3.f), vec3(0.f, 0.f, 180.f));

	idx = -1;
}

Scene02::~Scene02()
{
	delete m_Player;
	delete m_ObjectManager;

	delete m_Renderer;
	m_Renderer = nullptr;

	delete m_ObjectManager;
	m_ObjectManager = nullptr;
}

void Scene02::Init()
{
	// VBO Gen
	glGenBuffers(3, VBO);
	glGenTextures(1, &texture);

	// �÷��̾� ����
	m_Player = new Player(m_shaderProgramID, m_cameraController);

	// �� ����
	InitMap();

	// ������Ʈ ����
	InitObject();
}

void Scene02::InitMap()
{
	ObjectType type = ObjectType::WALL;

	float wall_bottom_y = -4.5f;
	float wall_side_y = 0.3f;

	// �ո� �޸�   -> (x, y, 0.2f)
	// ����		   -> (0.2f, y, z)
	// ���� �Ʒ��� -> (x, 0.2f, z)

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 15.0f, 0.2f, 15.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 15.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_side_y, -37.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 5.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 1.0f, wall_side_y, 37.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 5.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, -1.0f, wall_side_y, 37.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, -37.0f, wall_side_y, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, 37.0f, wall_side_y, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 5.0f, 0.2f, 15.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 1.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, 12.0f, wall_side_y, 1.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, -12.0f, wall_side_y, 1.0f);

}

void Scene02::InitObject()
{
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 0.0f), ObjectType::DEFAULT);
	m_ObjectManager->SetScale(idx, 1.0, 1.0f, 1.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, 0.4f, 0.0f);
}

void Scene02::Render()
{
	DrawView();
	DrawProjection();
	DrawLight();

	DrawStage2();
	DrawEndStage();
}

void Scene02::Update(float elapsedTime)
{
	m_Player->Update(elapsedTime);
	m_cameraController->Update(elapsedTime);
}

void Scene02::DrawView()
{
	unsigned int viewLocation = glGetUniformLocation(m_shaderProgramID, "viewTransform");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_cameraController->GetViewMatrix()));
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

void Scene02::DrawLight()
{
	m_Player->DrawPlayerLight();

	glUniform3fv(glGetUniformLocation(m_shaderProgramID, "pointLightPos"), 5, value_ptr(pointLightPositions[0]));
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
	TextureMapping(m_ObjectManager->m_ObjectList[idx]->m_type);

	glDrawArrays(DRAW_TYPE, 0, m_ObjectManager->m_ObjectList[idx]->m_vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	stbi_image_free(m_texture);
}

void Scene02::TextureMapping(ObjectType type)
{
	// Texture
	int widthImage, heightImage, numberOfChannel;
	// stbi_set_flip_vertically_on_load(true); //--- �̹����� �Ųٷ� �����ٸ� �߰�

	if (type == ObjectType::WALL)
	{
		m_texture = stbi_load("wall_texture.jfif", &widthImage, &heightImage, &numberOfChannel, 0);
	}
	else
	{
		m_texture = stbi_load("white.png", &widthImage, &heightImage, &numberOfChannel, 0);
	}


	unsigned int objTextureLocation = glGetUniformLocation(m_shaderProgramID, "outTexture");
	glUniform1i(objTextureLocation, 0);

	glActiveTexture(GL_TEXTURE0); //--- ���� 0�� Ȱ��ȭ
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture);
}

void Scene02::DrawEndStage()
{
}

void Scene02::DrawStage2()
{
	for (int i = 0; i < m_ObjectManager->m_ObjectList.size(); i++)
	{
		if (m_ObjectManager->m_ObjectList[i]->m_bActive)
		{
			DrawObject(m_ObjectManager->m_ObjectList[i]->m_DRAW_TYPE, m_ObjectManager->m_ObjectList[i]->m_model, i);
		}
	}
}
