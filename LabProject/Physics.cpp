#include "pch.h"
#include "Physics.h"

Physics::Physics(Player* player, ObjectManager* objMgr)
{
	m_Player = player;
	m_ObjectManager = objMgr;
}

Physics::~Physics()
{
	delete m_Player;
	m_Player = nullptr;

	delete m_ObjectManager;
	m_ObjectManager = nullptr;
}

void Physics::GetPlayerBBMin(float* x, float* y, float* z, vec3 movePos)
{
	*x = movePos.x - m_Player->m_scale.x / 2.f;
	*y = movePos.y - m_Player->m_scale.y / 2.f;
	*z = movePos.z - m_Player->m_scale.z / 2.f;
}

void Physics::GetPlayerBBMax(float* x, float* y, float* z, vec3 movePos)
{
	*x = movePos.x + m_Player->m_scale.x / 2.f;
	*y = movePos.y + m_Player->m_scale.y / 2.f;
	*z = movePos.z + m_Player->m_scale.z / 2.f;
}

bool Physics::BBOverlap_Player(Player* player, int srcID, vec3 movePos)
{
	if (player != NULL && m_ObjectManager->m_ObjectList[srcID] != NULL)
	{
		Object* src = m_ObjectManager->m_ObjectList[srcID];

		float srcMinX, srcMinY, srcMinZ;
		float srcMaxX, srcMaxY, srcMaxZ;

		float plyMinX, plyMinY, plyMinZ;
		float plyMaxX, plyMaxY, plyMaxZ;

		src->GetBBMin(&srcMinX, &srcMinY, &srcMinZ);
		src->GetBBMax(&srcMaxX, &srcMaxY, &srcMaxZ);

		GetPlayerBBMin(&plyMinX, &plyMinY, &plyMinZ, movePos);
		GetPlayerBBMax(&plyMaxX, &plyMaxY, &plyMaxZ, movePos);

		/*if (srcID == 5) cout << srcMinX << ", " << srcMinY << ", " << srcMinZ << endl;
		if (srcID == 5) cout << srcMaxX << ", " << srcMaxY << ", " << srcMaxZ << endl;*/

		if (plyMinX > srcMaxX)
			return false;
		if (plyMaxX < srcMinX)
			return false;
		if (plyMinY > srcMaxY)
			return false;
		if (plyMaxY < srcMinY)
			return false;
		if (plyMinZ > srcMaxZ)
			return false;
		if (plyMaxZ < srcMinZ)
			return false;

		return true;
	}

	return false;
}

bool Physics::BBOverlap_RayCast(vec3 viewPos, int srcID)
{
	if (m_ObjectManager->m_ObjectList[srcID] != NULL)
	{
		Object* src = m_ObjectManager->m_ObjectList[srcID];

		float srcMinX, srcMinY, srcMinZ;
		float srcMaxX, srcMaxY, srcMaxZ;

		src->GetBBMin(&srcMinX, &srcMinY, &srcMinZ);
		src->GetBBMax(&srcMaxX, &srcMaxY, &srcMaxZ);

		/*cout << "mouse X : " << viewPos.x << endl;
		cout << "minX : " << srcMinX << endl;
		cout << "maxX : " << srcMaxX << endl;
		cout << endl;
		cout << "mouse Y : " << viewPos.y << endl;
		cout << "minY : " << srcMinY << endl;
		cout << "maxY : " << srcMaxY << endl;*/

		if (viewPos.x > srcMaxX)
			return false;
		if (viewPos.x < srcMinX)
			return false;
		if (viewPos.y > srcMaxY)
			return false;
		if (viewPos.y < srcMinY)
			return false;
		if (viewPos.z > srcMaxZ)
			return false;
		if (viewPos.z < srcMinZ)
			return false;

		return true;
	}

	return false;
}

bool Physics::BBOverlap(int srcID, int dstID)
{
	if (m_ObjectManager->m_ObjectList[srcID] != NULL && m_ObjectManager->m_ObjectList[dstID] != NULL)
	{
		Object* src = m_ObjectManager->m_ObjectList[srcID];
		Object* dst = m_ObjectManager->m_ObjectList[dstID];

		float srcMinX, srcMinY, srcMinZ;
		float srcMaxX, srcMaxY, srcMaxZ;
		float dstMinX, dstMinY, dstMinZ;
		float dstMaxX, dstMaxY, dstMaxZ;
		src->GetBBMin(&srcMinX, &srcMinY, &srcMinZ);
		src->GetBBMax(&srcMaxX, &srcMaxY, &srcMaxZ);
		dst->GetBBMin(&dstMinX, &dstMinY, &dstMinZ);
		dst->GetBBMax(&dstMaxX, &dstMaxY, &dstMaxZ);

		if (srcMinX > dstMaxX)
			return false;
		if (srcMaxX < dstMinX)
			return false;
		if (srcMinY > dstMaxY)
			return false;
		if (srcMaxY < dstMinY)
			return false;
		if (srcMinZ > dstMaxZ)
			return false;
		if (srcMaxZ < dstMinZ)
			return false;

		return true;
	}

	return false;
}

float Physics::CheckRayCastingCollision(vec3 viewPos, int srcID)
{
	// Picking 적용 대상이 되는 오브젝트에서 Ray Casting Collision 체크
	return BBOverlap_RayCast(viewPos, srcID);
}

bool Physics::CheckCollisionPlayerByWall(vec3 movePos)
{
	for (int i = 1; i < m_ObjectManager->m_ObjectList.size(); i++)
	{
		if (m_ObjectManager->m_ObjectList[i]->m_type == ObjectType::WALL || m_ObjectManager->m_ObjectList[i]->m_type == ObjectType::DOOR)
		{
			if (BBOverlap_Player(m_Player, i, movePos))
			{
				return false;
			}
		}
	}

	return true;
}

void Physics::ApplyGravity()
{
	for (int i = 0; i < m_ObjectManager->m_ObjectList.size(); i++)
	{
		if (m_ObjectManager->m_ObjectList[i]->m_type == ObjectType::PICK)
		{
			if (m_ObjectManager->m_ObjectList[i]->GetPosition().y > -0.5f)
			{
				m_ObjectManager->m_ObjectList[i]->Move(0.0f, -0.1f, 0.0f);
			}
			else
			{
				m_ObjectManager->m_ObjectList[i]->m_position.y = -0.5f;
			}
		}
	}
}
