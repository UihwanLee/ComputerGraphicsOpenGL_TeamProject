#include "pch.h"

#pragma once
class Player
{
private:
	// 마우스 드래그에 따른 카메라 조작

	// Player Movement

public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);

private:
	// 입력 처리
};

