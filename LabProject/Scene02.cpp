#include "pch.h"
#include "Scene02.h"

Scene02::Scene02(GLuint shaderProgramID)
{
	m_shaderProgramID = shaderProgramID;
}

Scene02::~Scene02()
{
}

void Scene02::Init()
{
}

void Scene02::Render(float elapsedTime)
{
	DrawStage2(elapsedTime);
	DrawEndStage(elapsedTime);
}

void Scene02::Update(float elapsedTime)
{
}

void Scene02::DrawEndStage(float elapsedTime)
{
}

void Scene02::DrawStage2(float elapsedTime)
{
}
