#pragma once

class KeyBoard
{
public:
	void Init();
	void KeyDown(char key);
	void KeyUp(char key);


	void MouseDown(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	//누르고있을때
	bool Getbutton(KeyType key) { return GetState(key) == KeyState::PRESS; }

	//맨처음 눌렀을때
	bool GetbuttonDown(KeyType key) { return GetState(key) == KeyState::DOWN; }

	//맨처음 눌렀다가 땔대
	bool GetbuttonUp(KeyType key) { return GetState(key) == KeyState::UP; }

	vector<KeyState>& GetState() { return _states; }
	POINT& GetMousePos() { return _mousePos; }
	POINT& GetFirstMousePos() { return _firstmousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
	vector<KeyState> _states;

	POINT _mousePos = { 0,0 };
	POINT _firstmousePos = { 0,0 };

};