#include "pch.h"
#include "timeapi.h"
#include "Renderer.h"
#include "KeyBoard.h"
#include "CameraController.h"

Renderer* m_renderer = nullptr;

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
	m_renderer->UpdateAll(elapsedTimeInSec);
	m_renderer->DrawAll(elapsedTimeInSec);

	glutSwapBuffers();
}

void Idle()
{

	drawScene();
}

void MouseInput(int button, int state, int x, int y)
{
	KeyBoard::GetInstance()->MouseDown(button, state, x, y);
	CameraController::GetInstance()->MouseDown(button);
}

void MouseMove(int x, int y)
{
	KeyBoard::GetInstance()->MouseMove(x, y);
	CameraController::GetInstance()->MouseMove();
}

void KeyDownInput(unsigned char key, int x, int y)
{
	KeyBoard::GetInstance()->KeyDown(key);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	KeyBoard::GetInstance()->KeyUp(key);

}

void SpecialKeyDownInput(int id, int x, int y)
{

}

void SpecialKeyUpInput(int id, int x, int y)
{

}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
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
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	// 키보드
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	// 마우스
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);

	// 애니메이션
	glutIdleFunc(Idle);

	// 화면 출력
	g_startTime = timeGetTime();  // 시스템이 시작된 후 경과되는 시간을 ms로 받아준다.

	cout << "===========================================" << endl;
	cout << "===========================================" << endl;

	glutMainLoop();

	delete m_renderer;
}