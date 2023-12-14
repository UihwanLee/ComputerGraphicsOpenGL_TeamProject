#pragma once
#include "Enums.h"

class Scene01;
class Scene02;
class CameraController;

class SceneManager
{
public:
	void Init(CameraController*);

	void Update(float elapsedTime);
	void Render();

	void ChangeScene(SceneType sceneType);

	SceneType GetSceneType() const { return _sceneType; }

private:
	Scene01* m_scene1;
	Scene02* m_scene2;
	SceneType _sceneType = SceneType::NONE;

	CameraController* m_cameracontroller;
};


