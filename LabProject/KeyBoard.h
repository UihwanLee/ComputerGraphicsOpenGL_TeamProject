#pragma once



class KeyBoard
{
public:
	static KeyBoard* GetInstance()
	{
		static KeyBoard s_Insatance;
		return &s_Insatance;
	}

public:
	void Init();
	void KeyDown(char key);
	void KeyUp(char key);


	void MouseDown(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	//������������
	bool Getbutton(KeyType key) { return GetState(key) == KeyState::PRESS; }

	//��ó�� ��������
	bool GetbuttonDown(KeyType key) { return GetState(key) == KeyState::DOWN; }

	//��ó�� �����ٰ� ����
	bool GetbuttonUp(KeyType key) { return GetState(key) == KeyState::UP; }

	vector<KeyState>& GetState() { return _states; }
	POINT& GetMousePos() { return _mousePos; }
	POINT& GetFirstMousePos() { return _firstmousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
	vector<KeyState> _states;

	POINT _mousePos = { 0,0 }; // ���콺 ��ǥ
	POINT _firstmousePos = { 0,0 }; // ���콺 ��ǥ

};