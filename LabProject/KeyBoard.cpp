#include "pch.h"
#include "KeyBoard.h"

void KeyBoard::Init()
{
	_states.resize(KEY_TYPE_COUNT, KeyState::NONE);
}

void KeyBoard::KeyDown(char key)
{
	if (key == 'q')
		exit(1);

	KeyState& state = _states[key];
	state = KeyState::PRESS;

}

void KeyBoard::KeyUp(char key)
{
	KeyState& state = _states[key];
	state = KeyState::UP;
}

void KeyBoard::MouseDown(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		KeyState& m_state = _states[button];
		m_state = KeyState::PRESS;
		_firstmousePos.x = x;
		_firstmousePos.y = y;
	}
	else if (state == GLUT_UP) {
		KeyState& m_state = _states[button];
		m_state = KeyState::UP;

		_firstmousePos.x = x;
		_firstmousePos.y = y;
	}
}

void KeyBoard::MouseMove(int x, int y)
{
	KeyState& m_state = _states[LEFT_BUTTON];
	if (m_state == KeyState::PRESS) {
		_mousePos.x = x;
		_mousePos.y = y;
	}
}

