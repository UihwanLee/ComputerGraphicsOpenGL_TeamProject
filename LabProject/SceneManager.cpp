#include "pch.h"
#include "SceneManager.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Global.h"

void SceneManager::Init(CameraController* cameracontroller)
{
	m_cameracontroller = cameracontroller;

	m_scene1 = new Scene01(cameracontroller);
	_sceneType = SceneType::Scene1;

	m_scene2 = nullptr;
}

void SceneManager::Update(float elapsedTime)
{
	switch (_sceneType)
	{
	case SceneType::Scene1:
		m_scene1->Update(elapsedTime);
		break;
	case SceneType::Scene2:
		m_scene2->Update(elapsedTime);
		break;
	default:
		break;
	}

	if (g_change) {
		g_change = false;
		SceneType newType = static_cast<SceneType>(static_cast<int>(_sceneType) + 1);
		ChangeScene(newType);
	}
}

void SceneManager::Render()
{
	switch (_sceneType)
	{
	case SceneType::Scene1:
		m_scene1->Render();
		break;
	case SceneType::Scene2:
		m_scene2->Render();
		break;
	default:
		break;
	}

}


void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene01* newScene1 = nullptr;
	Scene02* newScene2 = nullptr;

	if (m_scene1)
	{
		delete m_scene1;
		m_scene1 = nullptr;
	}
	else if (m_scene2)
	{
		delete m_scene2;
		m_scene2 = nullptr;
	}

	_sceneType = sceneType;

	switch (_sceneType)
	{
	case SceneType::NONE:
		break;
	case SceneType::Scene1:
		newScene1 = new Scene01(m_cameracontroller);
		break;
	case SceneType::Scene2:
		newScene2 = new Scene02(m_cameracontroller);
		newScene2->Init();
		m_scene2 = newScene2;
		break;
	default:
		break;
	}
}
