#include "pch.h"
#include "timeapi.h"
#include "Renderer.h"
#include "KeyBoard.h"
#include "CameraController.h"
#include "LightController.h"
#include "Game.h"

Game* m_game = nullptr;
CameraController* m_cameraController = nullptr;

float r{ 0.0 }, g{ 0.0 }, b{ 0.0f };

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


	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// elapsed time (ms -> s)
	float elapsedTimeInSec = (float)elapsedTime / 1000.f;

	//cout << "elapsedTime      - " << elapsedTime << '\n'; 
	//cout << "elapsedTimeInSec - " << elapsedTimeInSec << '\n';


	// Renderer 
	m_game->UpdateAll(elapsedTimeInSec);
	m_game->DrawAll();

	glutSwapBuffers();
}

void Idle()
{

	drawScene();
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

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)
{

	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	// Initialize Renderer	
	m_cameraController = new CameraController();
	m_game = new Game(m_cameraController);


	glutDisplayFunc(drawScene);
	// glutReshapeFunc(Reshape);

	// Ű����
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	// ���콺
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);

	// �ִϸ��̼�
	glutIdleFunc(Idle);

	// ȭ�� ���
	g_startTime = timeGetTime();  // �ý����� ���۵� �� ����Ǵ� �ð��� ms�� �޾��ش�.

	cout << "===========================================" << endl;
	cout << "===========================================" << endl;

	glutMainLoop();

	delete m_game;
}