#pragma once
#include <cstdint>


#define LEFT_BUTTON 0x0000
#define RIGHT_BUTTON 0x0002

enum class KeyType
{
	//플레이어1
	W = 'w',
	A = 'a',
	S = 's',
	D = 'd',

	LeftMouse = LEFT_BUTTON,
	RightMouse = RIGHT_BUTTON,
};

enum class KeyState
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum ObjectType
{
	DEFAULT,
	WALL,
	TABLE,
	PICKING
};

enum class SceneType
{
	NONE,
	Scene1,
	Scene2,
	End,
};


enum
{
	KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int>(KeyState::END)
};