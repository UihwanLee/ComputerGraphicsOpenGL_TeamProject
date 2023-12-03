#include "pch.h"
#include "Game.h"
#include "CameraController.h"
#include "SceneManager.h"

Game::Game(CameraController* cameracontroller)
{
	m_SceneMgr = new SceneManager();
	m_SceneMgr->Init(cameracontroller);
}

Game::~Game()
{
	delete m_SceneMgr;
	m_SceneMgr = nullptr;
}


void Game::UpdateAll(float elapsedTime)
{
	m_SceneMgr->Update(elapsedTime);
}

void Game::DrawAll()
{
	m_SceneMgr->Render();
}