#include "pch.h"
#include "timeapi.h"
#include "Renderer.h"
#include "KeyBoard.h"
#include "CameraController.h"
#include "Game.h"

Game* m_game = nullptr;
CameraController* m_cameraController = nullptr;

DWORD g_startTime = 0;
DWORD g_prevTime = 0;

GLvoid drawScene()
{
	DWORD elapsedTime = 0;
	DWORD currenTime = timeGetTime();
	if (g_prevTime == 0) {
		elapsedTime = currenTime - g_startTime;
	}
	else {
		elapsedTime = currenTime - g_prevTime;
	}
	g_prevTime = currenTime;

	float r{ 0.f }, g{ 0.0f }, b{ 0.0f };
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float elapsedTimeInSec = (float)elapsedTime / 1000.f;

	m_game->UpdateAll(elapsedTimeInSec);
	m_game->DrawAll();

	glutSwapBuffers();
}

void Idle(void)
{
	drawScene();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MouseInput(int button, int state, int x, int y)
{
	m_cameraController->MouseDown(button, state, x, y);
}

void MouseMove(int x, int y)
{
	m_cameraController->MouseMove(x, y);
}

void KeyDownInput(unsigned char key, int x, int y)
{
	m_cameraController->KeyDown(key);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	m_cameraController->KeyUp(key);

}

void SpecialKeyDownInput(int id, int x, int y)
{

}

void SpecialKeyUpInput(int id, int x, int y)
{

}

int main(int argc, char** argv)
{

	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	// Initialize Renderer	
	m_cameraController = new CameraController();
	m_game = new Game(m_cameraController);

	glutDisplayFunc(drawScene);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	// 키보드
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	// 마우스
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);

	// 화면 출력
	g_startTime = timeGetTime();

	cout << "===========================================" << endl;
	cout << "===========================================" << endl;

	glutMainLoop();

	delete m_game;
}