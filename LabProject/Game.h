#pragma once

class CameraController;

class Game
{
public:
	Game(CameraController*);
	~Game();

public:
	void UpdateAll(float elapsedTime);
	void  DrawAll();


private:
	class SceneManager* m_SceneMgr;
};

