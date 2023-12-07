#include "pch.h"
#include "Scene02.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float nPointLightPositions = 20;
vec3 pointLightPositions[20] = {
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(4.0f,  0.0f, 0.0f),
		glm::vec3(-4.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 7.0f),
		glm::vec3(0.0f,  0.0f, 15.0f),
		glm::vec3(0.0f,  0.0f, 26.0f),
		glm::vec3(0.0f,  0.0f, 26.0f),
		glm::vec3(0.0f,  0.0f, 26.0f),
		glm::vec3(0.0f,  0.0f, 42.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(0.0f,  0.0f, 0.0f)
};

Scene02::Scene02(CameraController* cameracontroller)
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_ObjectManager = new ObjectManager(m_Renderer->GetShaderProgramID(), cameracontroller);

	m_shaderProgramID = m_Renderer->GetShaderProgramID();

	m_cameraController = cameracontroller;
	m_cameraController->Init(vec3(0.f, 0.0f, -3.f), vec3(0.f, 0.f, 180.f));

	idx = -1;
}

Scene02::~Scene02()
{
	delete m_Player;
	m_Player = nullptr;

	for (int i = 0; i < m_ObjectManager->m_ObjectList.size(); i++)
	{
		delete m_ObjectManager->m_ObjectList[i];
		m_ObjectManager->m_ObjectList[i] = nullptr;
	}

	delete m_ObjectManager;
	m_ObjectManager = nullptr;

	delete m_Renderer;
	m_Renderer = nullptr;

	delete m_ObjectManager;
	m_ObjectManager = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Scene02::Init()
{
	// VBO Gen
	glGenBuffers(3, VBO);
	glGenTextures(1, &texture);

	// 플레이어 생성
	m_Player = new Player(m_shaderProgramID, m_cameraController, vec3(1.0f, 0.1f, 1.0f));

	m_Physics = new Physics(m_Player, m_ObjectManager);

	// m_cameraController->SetPhysics(m_Physics);

	// 맵 생성
	InitMap();

	// 오브젝트 생성
	InitObject();
}

void Scene02::InitMap()
{
	ObjectType type = ObjectType::WALL;

	float wall_bottom_y = -1.0f;
	float wall_side_y = 0.3f;

	// 앞면 뒷면   -> (x, y, 0.2f)
	// 옆면		   -> (0.2f, y, z)
	// 윗면 아랫면 -> (x, 0.2f, z)

	// 시작 단계
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 15.0f, 0.2f, 15.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 15.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_side_y, -7.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 5.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 5.0f, wall_side_y, 7.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 5.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, -5.0f, wall_side_y, 7.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, -7.5f, wall_side_y, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, 7.5f, wall_side_y, 0.0f);

	// 통로1
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 6.0f, 0.2f, 15.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 15.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, 3.0f, wall_side_y, 15.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 15.0f);
	m_ObjectManager->SetPosition(idx, -3.0f, wall_side_y, 15.0f);

	// 재단 방1
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 8.0f);
	m_ObjectManager->SetPosition(idx, -5.0f, wall_side_y, 26.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 2.5f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, -4.2f, wall_side_y, 22.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 2.5f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, -4.2f, wall_side_y, 30.5f);

	// 통로2
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 6.0f, 0.2f, 8.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 34.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 8.0f);
	m_ObjectManager->SetPosition(idx, 3.0f, wall_side_y, 34.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 8.0f);
	m_ObjectManager->SetPosition(idx, -3.0f, wall_side_y, 34.5f);

	// 재단 오브젝트 방
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 10.0f, 0.2f, 5.0f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_bottom_y, 41.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 2.5f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, -4.2f, wall_side_y, 38.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 2.5f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 4.2f, wall_side_y, 38.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 10.0f, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 0.0f, wall_side_y, 43.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 5.0f);
	m_ObjectManager->SetPosition(idx, -4.2f, wall_side_y, 41.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 0.2f, 5.0f, 5.0f);
	m_ObjectManager->SetPosition(idx, 4.2f, wall_side_y, 41.0f);

	// 긴 통로
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 30.0f, 0.2f, 8.0f);
	m_ObjectManager->SetPosition(idx, 8.0f, wall_bottom_y, 26.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), type);
	m_ObjectManager->SetScale(idx, 24.0, 5.0f, 0.2f);
	m_ObjectManager->SetPosition(idx, 15.0f, wall_side_y, 22.5f);
}

void Scene02::InitObject()
{
	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 0.0f), ObjectType::DEFAULT);
	m_ObjectManager->SetPosition(idx, 0.0f, 0.4f, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(1.0f, 1.0f, 1.0f), ObjectType::DEFAULT);
	m_ObjectManager->SetScale(idx, 1.0f, 0.75f, 2.5f);
	m_ObjectManager->SetPosition(idx, -4.5f, -0.75f, 26.5f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(0.0f, 1.0f, 0.0f), ObjectType::PICK);
	m_ObjectManager->SetPosition(idx, 5.0f, -0.5f, 0.0f);

	m_ObjectManager->CreateCube(&idx, highp_vec3(0.0f, 0.0f, 1.0f), ObjectType::PICK);
	m_ObjectManager->SetPosition(idx, -5.0f, -0.5f, 0.0f);
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
	InputKey(elapsedTime);
	InputMouse();
	ApplyGravity();
}

void Scene02::InputMouse()
{
	if (m_cameraController->IsMouseDown())
	{
		// 오브젝트 피킹 검사
		CheckRayCastingCollision();
	}

	if (m_cameraController->IsMouseUp())
	{
		// PICKING 오브젝트 놓기
		ResetRayCastingCollision();
	}
}

void Scene02::InputKey(float elapsedTime)
{
	if (m_cameraController->InputKeyW())
	{
		if (m_Physics->CheckCollisionPlayerByWall(m_cameraController->TryMoveFront(elapsedTime)))
		{
			m_cameraController->MoveFront(elapsedTime);
		}
	}
	if (m_cameraController->InputKeyS())
	{
		if (m_Physics->CheckCollisionPlayerByWall(m_cameraController->TryMoveBack(elapsedTime)))
		{
			m_cameraController->MoveBack(elapsedTime);
		}
	}
	if (m_cameraController->InputKeyA())
	{
		if (m_Physics->CheckCollisionPlayerByWall(m_cameraController->TryMoveLeft(elapsedTime)))
		{
			m_cameraController->MoveLeft(elapsedTime);
		}
	}
	if (m_cameraController->InputKeyD())
	{
		if (m_Physics->CheckCollisionPlayerByWall(m_cameraController->TryMoveRight(elapsedTime)))
		{
			m_cameraController->MoveRight(elapsedTime);
		}
	}
}

void Scene02::CheckRayCastingCollision()
{
	float pickID = 0;
	float curDist = 9999.0f;
	vector<float> rayList = { 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f, 0.0f };
	for (int i = 0; i < rayList.size(); i++)
	{
		float rayDist = rayList[i];
		for (int idx = 0; idx < m_ObjectManager->m_ObjectList.size(); idx++)
		{
			if (m_ObjectManager->m_ObjectList[idx]->m_type == ObjectType::PICK)
			{
				vec3 viewPos = m_cameraController->TryMoveFront(rayDist);
				if (m_Physics->CheckRayCastingCollision(viewPos, idx))
				{
					m_ObjectManager->m_ObjectList[idx]->ChangeType(ObjectType::PICKING);
				}
			}
		}
	}
}

void Scene02::ResetRayCastingCollision()
{
	// 피킹된 오브젝트 놓기
	for (int idx = 1; idx < m_ObjectManager->m_ObjectList.size(); idx++)
	{
		if (m_ObjectManager->m_ObjectList[idx]->m_type == ObjectType::PICKING)
		{
			m_ObjectManager->m_ObjectList[idx]->ChangeType(ObjectType::PICK);
		}
	}
}

bool Scene02::CheckCollisionPlayerByWall(vec3 movePos)
{
	return m_Physics->CheckCollisionPlayerByWall(movePos);
}

void Scene02::ApplyGravity()
{
	m_Physics->ApplyGravity();
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

	// 원근 투영
	float fov = 45.0f; // 시야각 (Field of View)
	float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // 화면의 가로 세로 비율
	float zNear = 0.1f; // 가까운 클리핑 평면
	float zFar = 50.0f; // 먼 클리핑 평면
	projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar); //--- 투영 공간 설정: (뷰잉각도, 종횡비, 가까운거리, 먼거리)

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);		// 투영변환
}

void Scene02::DrawLight()
{
	m_Player->DrawPlayerLight();

	glUniform3fv(glGetUniformLocation(m_shaderProgramID, "pointLightPos"), nPointLightPositions, value_ptr(pointLightPositions[0]));
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
	// stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가

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

	glActiveTexture(GL_TEXTURE0); //--- 유닛 0을 활성화
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
