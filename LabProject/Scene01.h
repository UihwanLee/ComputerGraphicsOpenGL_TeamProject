#pragma once

class CameraController;


class Scene01
{

public:
	Scene01(CameraController*);
	~Scene01();

	void Init();

	void Update(float elapsedTime);
	void Render();

private:
	//void DrawStartStage();
	//void DrawStage1();

	//void CreateVertexBufferObjectBox();

private:
	class Renderer* m_Renderer;
	class ObjectManager* m_ObjectMgr;
};

