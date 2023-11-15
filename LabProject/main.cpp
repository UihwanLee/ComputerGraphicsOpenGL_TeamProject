#include "pch.h"
#include "timeapi.h"
#include "Renderer.h"

Renderer* m_renderer = nullptr;

float r{ 0.46666f }, g{ 0.533333f }, b{ 0.6f };

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
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	// �ִϸ��̼�
	glutIdleFunc(Idle);

	// ȭ�� ���
	g_startTime = timeGetTime();  // �ý����� ���۵� �� ����Ǵ� �ð��� ms�� �޾��ش�.

	cout << "===========================================" << endl;
	cout << "c - �ܼ� ��� on / off" << endl;
	cout << "+ - ���ǵ� Up" << endl;
	cout << "- - ���ǵ� Down" << endl;
	cout << "L - ���� on / off" << endl;
	cout << "===========================================" << endl;

	glutMainLoop();

	delete m_renderer;
}