#include "pch.h"
#include "Scene02.h"

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
	glGenBuffers(2, VBO);

	// 플레이어 생성
	m_Player = new Player();
	m_Player->CreatPlayerMesh();

	// 오브젝트 생성
	m_ObjectManager = new ObjectManager();

	m_ObjectManager->CreateCube(highp_vec3(1.0f, 0.0f, 0.0f));
	m_ObjectManager->SetScale(0, 2.0f, 0.1f, 2.0f);

}

void Scene02::Render(float elapsedTime)
{
	DrawView();
	DrawProjection();
	DrawPlayerLight();
	DrawPlayer();

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

	glm::vec3 cameraPos = glm::vec3(m_Player->m_CameraPos.x, m_Player->m_CameraPos.y, m_Player->m_CameraPos.z); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(m_Player->m_AT.x, m_Player->m_AT.y, m_Player->m_AT.z); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);

	//view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);		// 뷰변환
}

void Scene02::DrawProjection()
{
	unsigned int projectionLocation = glGetUniformLocation(m_shaderProgramID, "projectionTransform");

	glm::mat4 projection = glm::mat4(1.0f);

	// 직교 투영
	float left = -1.0f;
	float right = 1.0f;
	float bottom = -1.0f;
	float top = 1.0f;
	float zNear = -10.0f;
	float zFar = 10.0f;
	projection = glm::ortho(left, right, bottom, top, zNear, zFar);

	// 원근 투영
	//float fov = 45.0f; // 시야각 (Field of View)
	//float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // 화면의 가로 세로 비율
	//float zNear = 0.1f; // 가까운 클리핑 평면
	//float zFar = 50.0f; // 먼 클리핑 평면
	//projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar); //--- 투영 공간 설정: (뷰잉각도, 종횡비, 가까운거리, 먼거리)

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);		// 투영변환
}

void Scene02::DrawPlayerLight()
{
	unsigned int lightPosLocation = glGetUniformLocation(m_shaderProgramID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, m_Player->m_LightPos.x, m_Player->m_LightPos.y, m_Player->m_LightPos.z);
	unsigned int lightColorLocation = glGetUniformLocation(m_shaderProgramID, "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, m_Player->m_LightColor.r, m_Player->m_LightColor.g, m_Player->m_LightColor.b);
	unsigned int viewPosLocation = glGetUniformLocation(m_shaderProgramID, "viewPos"); //--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, 0.0f, 0.0f, 0.0f);
}

void Scene02::DrawPlayer()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, m_Player->m_vertices.size() * sizeof(glm::vec3), &m_Player->m_vertices[0], GL_STATIC_DRAW);

	// 모델변환
	unsigned int modelLocation = glGetUniformLocation(m_shaderProgramID, "modelTransform");
	m_Player->m_model = m_Player->TransformModel();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_Player->m_model));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, m_Player->m_normals.size() * sizeof(glm::vec3), &m_Player->m_normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	unsigned int objColorLocation = glGetUniformLocation(m_shaderProgramID, "objectColor"); //--- object Color값 전달 
	glUniform3f(objColorLocation, m_Player->m_colors.r, m_Player->m_colors.g, m_Player->m_colors.b);


	glDrawArrays(m_Player->m_DRAW_TYPE, 0, m_Player->m_vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene02::DrawObject(int DRAW_TYPE, glm::mat4& model, int idx)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, m_ObjectManager->m_ObjectList[idx]->m_vertices.size() * sizeof(glm::vec3), &m_ObjectManager->m_ObjectList[idx]->m_vertices[0], GL_STATIC_DRAW);

	// 모델변환
	unsigned int modelLocation = glGetUniformLocation(m_shaderProgramID, "modelTransform");
	m_ObjectManager->m_ObjectList[idx]->m_model = m_ObjectManager->TransformModel(idx);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_ObjectManager->m_ObjectList[idx]->m_model));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, m_ObjectManager->m_ObjectList[idx]->m_normals.size() * sizeof(glm::vec3), &m_ObjectManager->m_ObjectList[idx]->m_normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	unsigned int objColorLocation = glGetUniformLocation(m_shaderProgramID, "objectColor"); //--- object Color값 전달 
	glUniform3f(objColorLocation, m_ObjectManager->m_ObjectList[idx]->m_colors.r, m_ObjectManager->m_ObjectList[idx]->m_colors.g, m_ObjectManager->m_ObjectList[idx]->m_colors.b);


	glDrawArrays(DRAW_TYPE, 0, m_ObjectManager->m_ObjectList[idx]->m_vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
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
