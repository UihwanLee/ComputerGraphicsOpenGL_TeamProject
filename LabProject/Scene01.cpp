#include "pch.h"
#include "Scene01.h"
#include "ObjectManager.h"
#include "Renderer.h"

Scene01::Scene01(CameraController* cameracontroller)
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_ObjectMgr = new ObjectManager();
	m_ObjectMgr->Init(cameracontroller);
	CreateStage1Map();
}

Scene01::~Scene01()
{
	delete m_Renderer;
	m_Renderer = nullptr;

	delete m_ObjectMgr;
	m_ObjectMgr = nullptr;

}

void Scene01::Init()
{
}

void Scene01::CreateStage1Map()
{
	Object* rinty = new Object();;
	rinty->SetPosition(vec3(-15.f, -5.f, -150.f));
	rinty->SetRotate(vec3(0.f, 1.f, 0.f));
	rinty->SetScale(vec3(5.f, 5.f, 5.f));
	rinty->SetType(ObjectType::Rinty);
	rinty->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(rinty);

	float size_x = 30.f;
	float size_y = 10.f;
	float size_z = 40.f;
	Object* wal1 = new Object();
	wal1->SetPosition(vec3(0.f, 0.0f, 0.f));
	wal1->SetScale(vec3(size_x, size_y, 0.1f));
	wal1->SetType(ObjectType::Cube);
	wal1->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal1);

	Object* wal2 = new Object();
	wal2->SetPosition(vec3(0.f, -size_y / 2, -size_z / 2));
	wal2->SetScale(vec3(size_x, 0.1f, size_z));
	wal2->SetType(ObjectType::Cube);
	wal2->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal2);


	Object* wal4 = new Object();
	wal4->SetPosition(vec3(-size_x / 2, 0.f, -size_z / 2));
	wal4->SetScale(vec3(0.1f, size_y, size_z));
	wal4->SetType(ObjectType::Cube);
	wal4->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal4);

	Object* wal5 = new Object();
	wal5->SetPosition(vec3(size_x / 2, 0.f, -size_z / 2));
	wal5->SetScale(vec3(0.1f, size_y, size_z));
	wal5->SetType(ObjectType::Cube);
	wal5->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal5);

	float gap_x = 10.f;
	float xx = size_x - (size_x / 2 - gap_x);
	Object* wal6 = new Object();
	wal6->SetPosition(vec3(xx / 2, 0.f, -size_z));
	wal6->SetScale(vec3(size_x / 2 - gap_x, size_y, 0.1f));
	wal6->SetType(ObjectType::Cube);
	wal6->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal6);

	Object* wal7 = new Object();
	wal7->SetPosition(vec3(-xx / 2, 0.f, -size_z));
	wal7->SetScale(vec3(size_x / 2 - gap_x, size_y, 0.1f));
	wal7->SetType(ObjectType::Cube);
	wal7->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal7);

	float load_z = 100.f;

	Object* wal8 = new Object();
	wal8->SetPosition(vec3(size_x / 2 - gap_x / 2, 0.f, -load_z / 2 - size_z));
	wal8->SetScale(vec3(0.1f, size_y, load_z));
	wal8->SetType(ObjectType::Cube);
	wal8->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal8);

	Object* wal9 = new Object();
	wal9->SetPosition(vec3(-(size_x / 2 - gap_x / 2), 0.f, -load_z / 2 - size_z));
	wal9->SetScale(vec3(0.1f, size_y, load_z));
	wal9->SetType(ObjectType::Cube);
	wal9->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal9);

	Object* wal10 = new Object();
	wal10->SetPosition(vec3(0.f, -size_y / 2, -load_z / 2 - size_z));
	wal10->SetScale(vec3(size_x - gap_x, 0.1f, load_z));
	wal10->SetType(ObjectType::Cube);
	wal10->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal10);


	// =======================

	Object* wal12 = new Object();
	float move_x = (size_x - gap_x) / 2 + size_x / 4;
	wal12->SetPosition(vec3(-move_x, 0.f, -load_z - size_z));
	wal12->SetScale(vec3(size_x / 2, size_y, 0.1));
	wal12->SetType(ObjectType::Cube);
	wal12->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal12);

	Object* wal13 = new Object();
	wal13->SetPosition(vec3(-move_x - size_x / 4, 0.f, -load_z - size_z - (size_z / 4)));
	wal13->SetScale(vec3(0.1, size_y, size_z / 2));
	wal13->SetType(ObjectType::Cube);
	wal13->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal13);

	Object* wal14 = new Object();
	wal14->SetPosition(vec3(-move_x, 0.f, -load_z - size_z - size_z / 2));
	wal14->SetScale(vec3(size_x / 2, size_y, 0.1));
	wal14->SetType(ObjectType::Cube);
	wal14->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal14);

	Object* wal15 = new Object();
	wal15->SetPosition(vec3(-17.5f, -size_y / 2, -150.f));
	wal15->SetScale(vec3(size_x / 2, 0.1, size_z / 2));
	wal15->SetType(ObjectType::Cube);
	wal15->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal15);


	Object* wal18 = new Object();
	wal18->SetPosition(vec3(0.f, -size_y / 2, -190.f));
	wal18->SetScale(vec3(size_x - gap_x, 0.1f, load_z));
	wal18->SetType(ObjectType::Cube);
	wal18->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal18);

	// ===================

	Object* wal19 = new Object();
	wal19->SetPosition(vec3(size_x / 2 + gap_x, 0.f, -load_z - size_z));
	wal19->SetScale(vec3(size_x, size_y, 0.1));
	wal19->SetType(ObjectType::Cube);
	wal19->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal19);

	Object* wal20 = new Object();
	wal20->SetPosition(vec3(gap_x + size_x, 0.f, -160.f));
	wal20->SetScale(vec3(0.1, size_y, size_z));
	wal20->SetType(ObjectType::Cube);
	wal20->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal20);


	Object* wal21 = new Object();
	wal21->SetPosition(vec3(size_x / 2 + gap_x, 0.f, -load_z - size_z * 2));
	wal21->SetScale(vec3(size_x, size_y, 0.1));
	wal21->SetType(ObjectType::Cube);
	wal21->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal21);

	Object* wal22 = new Object();
	wal22->SetPosition(vec3(size_x / 2 + gap_x, -size_y / 2, -load_z - size_z * 1.5));
	wal22->SetScale(vec3(size_x, 0.1, size_z));
	wal22->SetType(ObjectType::Cube);
	wal22->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal22);


	// ========================
	Object* wal24 = new Object();
	wal24->SetPosition(vec3(-10.f, 0.f, -200.f));
	wal24->SetScale(vec3(0.1, size_y, size_z * 2));
	wal24->SetType(ObjectType::Cube);
	wal24->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal24);

	Object* wal25 = new Object();
	wal25->SetPosition(vec3(10.f, 0.f, -210.f));
	wal25->SetScale(vec3(0.1, size_y, size_z * 1.5));
	wal25->SetType(ObjectType::Cube);
	wal25->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal25);

	// ========================
	Object* wal26 = new Object();
	wal26->SetPosition(vec3(-10.f, 0.f, -290.f));
	wal26->SetScale(vec3(0.1, size_y, load_z));
	wal26->SetType(ObjectType::Cube);
	wal26->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal26);

	Object* wal27 = new Object();
	wal27->SetPosition(vec3(10.f, 0.f, -240.f - (load_z * 1.25f) / 2));
	wal27->SetScale(vec3(0.1, size_y, load_z * 1.25f));
	wal27->SetType(ObjectType::Cube);
	wal27->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal27);


	Object* wal29 = new Object();
	wal29->SetPosition(vec3(0.f, -size_y / 2, -290.f));
	wal29->SetScale(vec3(size_x - gap_x, 0.1f, load_z));
	wal29->SetType(ObjectType::Cube);
	wal29->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal29);

	// ========================

	Object* wal30 = new Object();
	wal30->SetPosition(vec3(-size_x - gap_x, 0.f, -340.f));
	wal30->SetScale(vec3(size_x * 2, size_y, 0.1f));
	wal30->SetType(ObjectType::Cube);
	wal30->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal30);


	Object* wal31 = new Object();
	wal31->SetPosition(vec3(-70.f, 0.f, -390.f));
	wal31->SetScale(vec3(0.1f, size_y, load_z));
	wal31->SetType(ObjectType::Cube);
	wal31->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal31);

	Object* wal32 = new Object();
	wal32->SetPosition(vec3(0.f, 0.f, -440.f));
	wal32->SetScale(vec3(140.f, size_y, 0.1f));
	wal32->SetType(ObjectType::Cube);
	wal32->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal32);

	Object* wal33 = new Object();
	wal33->SetPosition(vec3(size_x + gap_x, 0.f, -365.f));
	wal33->SetScale(vec3(size_x * 2, size_y, 0.1f));
	wal33->SetType(ObjectType::Cube);
	wal33->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal33);

	Object* wal34 = new Object();
	wal34->SetPosition(vec3(70.f, 0.f, -390.f + 12.5f));
	wal34->SetScale(vec3(0.1f, size_y, 25.f));
	wal34->SetType(ObjectType::Cube);
	wal34->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal34);

	Object* wal35 = new Object();
	wal35->SetPosition(vec3(70.f, 0.f, -390.f + 12.5f - 50.f));
	wal35->SetScale(vec3(0.1f, size_y, 25.f));
	wal35->SetType(ObjectType::Cube);
	wal35->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal35);

	Object* wal36 = new Object();
	wal36->SetPosition(vec3(-30.f, -size_y / 2, -390.f));
	wal36->SetScale(vec3(80.f, 0.1f, 100.f));
	wal36->SetType(ObjectType::Cube);
	wal36->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal36);

	Object* wal38 = new Object();
	wal38->SetPosition(vec3(40.f, -size_y / 2, -402.5f));
	wal38->SetScale(vec3(60.f, 0.1f, 75.f));
	wal38->SetType(ObjectType::Cube);
	wal38->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal38);

	// ========================
	Object* wal40 = new Object();
	wal40->SetPosition(vec3(100.f, 0.f, -390.f));
	wal40->SetScale(vec3(size_x * 2, size_y, 0.1f));
	wal40->SetType(ObjectType::Cube);
	wal40->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal40);

	Object* wal41 = new Object();
	wal41->SetPosition(vec3(100.f, 0.f, -415.f));
	wal41->SetScale(vec3(size_x * 2, size_y, 0.1f));
	wal41->SetType(ObjectType::Cube);
	wal41->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal41);

	Object* wal42 = new Object();
	wal42->SetPosition(vec3(100.f, -size_y / 2, -402.5f));
	wal42->SetScale(vec3(size_x * 2, 0.1f, 25.f));
	wal42->SetType(ObjectType::Cube);
	wal42->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal42);

	// ========================
	Object* wal43 = new Object();
	wal43->SetPosition(vec3(130.f, 0.f, -415.f - 20.f));
	wal43->SetScale(vec3(0.1f, size_y, 40.f));
	wal43->SetType(ObjectType::Cube);
	wal43->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal43);

	Object* wal44 = new Object();
	wal44->SetPosition(vec3(130.f, 0.f, -390.f + 30.f));
	wal44->SetScale(vec3(0.1f, size_y, 60.f));
	wal44->SetType(ObjectType::Cube);
	wal44->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal44);

	Object* wal45 = new Object();
	wal45->SetPosition(vec3(160.f, 0.f, -415.f - 40.f));
	wal45->SetScale(vec3(60.f, size_y, 0.1f));
	wal45->SetType(ObjectType::Cube);
	wal45->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal45);

	Object* wal46 = new Object();
	wal46->SetPosition(vec3(160.f, 0.f, -390.f + 60.f));
	wal46->SetScale(vec3(60.f, size_y, 0.1f));
	wal46->SetType(ObjectType::Cube);
	wal46->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal46);

	Object* wal47 = new Object();
	wal47->SetPosition(vec3(190.f, 0.f, -390.f - 2.5f));
	wal47->SetScale(vec3(0.1f, size_y, 125.f));
	wal47->SetType(ObjectType::Cube);
	wal47->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal47);

	Object* wal48 = new Object();
	wal48->SetPosition(vec3(160.f, -size_y / 2, -390.f - 2.5f));
	wal48->SetScale(vec3(60.f, 0.1f, 125.f));
	wal48->SetType(ObjectType::Cube);
	wal48->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(wal48);

	// ========================
	Object* prop = new Object();
	prop->SetPosition(vec3(25.f, -size_y / 2 + 1.f, -160.f));
	prop->SetScale(vec3(20.f, 2.f, 25.f));
	prop->SetType(ObjectType::Prop);
	prop->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(prop);

	Object* stone = new Object();	// 석상
	stone->SetPosition(vec3(25.f, -size_y / 2 + 4.f, -160.f));
	stone->SetScale(vec3(5.f, 5.f, 5.f));
	stone->SetType(ObjectType::Stone);
	stone->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(stone);

	// ========================
	Object* prop2 = new Object();
	prop2->SetPosition(vec3(-55.f, -size_y / 2 + 1.f, -390.f - 30.f));
	prop2->SetScale(vec3(20.f, 2.f, 25.f));
	prop2->SetType(ObjectType::Prop);
	wal30->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(prop2);

	// ========================
	Object* door = new Object(); // 문
	door->SetPosition(vec3(70.f, 0.f, -390.f - 12.5f));
	door->SetScale(vec3(0.1f, size_y, 25.f));
	door->SetType(ObjectType::Door);
	door->SetClose(false);
	door->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(door);


	// ========================
	Object* blink = new Object();
	blink->SetPosition(vec3(0.f, -5.f, -340.f));
	blink->SetRotate(vec3(0.f, 1.f, 0.f));
	blink->SetScale(vec3(5.f, 5.f, 5.f));
	blink->SetType(ObjectType::Blink);
	wal30->Setid(idx++);
	m_ObjectMgr->GetObjectList().push_back(blink);

	// ========================
	Object* stone2 = new Object();	// 다음  씬으로 가기위한
	stone2->SetPosition(vec3(180.f, -size_y / 2 + 5.f / 2, -340.f));
	stone2->SetScale(vec3(5.f));
	stone2->SetType(ObjectType::Stone);
	stone2->Setid(idx);
	m_nextScene = idx++;
	m_ObjectMgr->GetObjectList().push_back(stone2);

}

void Scene01::Update(float elapsedTime)
{
	m_ObjectMgr->Update(elapsedTime);

}
void Scene01::Render()
{
	m_ObjectMgr->Render(m_Renderer);
}