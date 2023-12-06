#pragma once
#include "Player.h"
#include "ObjectManager.h"

class Physics
{
private:
	Player*			m_Player;
	ObjectManager*	m_ObjectManager;

public:
	Physics(Player* player, ObjectManager* ObjectManager);
	~Physics();

	void GetPlayerBBMin(float* x, float* y, float* z, vec3 movePos);
	void GetPlayerBBMax(float* x, float* y, float* z, vec3 movePos);

	bool BBOverlap_Player(Player* player, int srcID, vec3 movePos);
	bool BBOverlap(int srcID, int dstID);

	bool CheckRayCastingCollision();
	bool CheckCollisionPlayerByWall(vec3 movePos);
};

