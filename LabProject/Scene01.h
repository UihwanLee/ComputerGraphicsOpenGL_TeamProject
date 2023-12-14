#pragma once

class Scene01
{

public:
	Scene01(class CameraController*);
	~Scene01();

	void Init();
	void CreateStage1Map();

	void Update(float elapsedTime);
	void Render();

private:

	class Renderer* m_Renderer;
	class ObjectManager* m_ObjectMgr;
	int idx{};
	int m_nextScene{};
};

