#pragma once


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

enum class SceneType
{
	NONE,
	Scene1,
	Scene2,
	End,
};

enum class ObjectType {
	Cube,		// 벽
	Prop,		// 석상 받침대
	Stone,		// 석상
	Door,		// 문
	Rinty,		// 링티
	Player,		// 플레이어
	Blink,		// 놀래켜 주는 거

	// =============
	DEFAULT,
	WALL,
	DOOR,
	TABLE,
	PICK,
	PICKING,
	STICK,

	None,
};

enum
{
	KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int>(KeyState::END)
};