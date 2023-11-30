#include "pch.h"
#include "Object.h"

#pragma once
class Player : public Object
{
public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Render(float elapsedTime);
};

