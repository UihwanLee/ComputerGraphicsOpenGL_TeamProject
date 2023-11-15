#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

GLvoid KeyboardDown(unsigned char key, int x, int y)
{

}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{

}

GLvoid SpecialDownKey(int key, int x, int y)
{

}

GLvoid SpecialUpKey(int key, int x, int y)
{

}

void Mouse(int button, int state, int x, int y)
{

}

void Motion(int x, int y)
{

}


void Player::Update(float elapsedTime)
{
	// 마우스
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	// 키보드
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

	glutSpecialFunc(SpecialDownKey);
	glutSpecialUpFunc(SpecialUpKey);
}

void Player::Render(float elapsedTime)
{
}

// Player 입력
