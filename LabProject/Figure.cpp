#include "pch.h"
#include "Figure.h"

GLfloat Figure::CoordinateVertexs[18] = {
	1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f
};

GLfloat Figure::CoordinateColors[18] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
};

GLfloat Figure::CubeVertexs[24] = {
			-0.5f, 0.5f, -0.5f,  //0번점
			-0.5f, 0.5f, 0.5f,  //1번점
			0.5f, 0.5f, 0.5f,  //2번점
			0.5f, 0.5f, -0.5f,  //3번점

			-0.5f, -0.5f, -0.5f,  //4번점
			-0.5f, -0.5f, 0.5f,  //5번점
			0.5f, -0.5f, 0.5f,  //6번점
			0.5f, -0.5f, -0.5f,  //7번점
};

GLfloat Figure::CubeColors[24] = {
			0.0f, 1.0f, 0.0f,  //0번점
			0.0f, 1.0f, 1.0f,  //1번점
			0.0f, 1.0f, 0.0f,  //2번점
			1.0f, 1.0f, 0.0f,  //3번점

			1.0f, 0.0f, 1.0f,  //4번점
			0.0f, 0.0f, 1.0f,  //5번점
			0.0f, 0.0f, 0.0f,  //6번점
			1.0f, 0.0f, 0.0f,  //7번점
};

GLint Figure::CubeIndexs[36] =
{
	0,1,2,
	0,2,3,  //윗면

	1,5,6,
	1,6,2, //앞면

	2,6,7,
	2,7,3, //우측면

	0,4,5,
	0,5,1, //좌측면

	5,4,6,
	4,7,6,// 밑면

	0,7,4, //뒷면
	0,3,7
};

GLfloat Figure::TetrahedronVertexs[12] =
{
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.5f,
};

GLfloat Figure::TetrahedronColors[12] =
{
	135.f / 255.f,206.f / 255.f,235.f / 255.f,
	135.f / 255.f,206.f / 255.f,235.f / 255.f,
	135.f / 255.f,206.f / 255.f,235.f / 255.f,
	135.f / 255.f,206.f / 255.f,235.f / 255.f,
};

GLint Figure::TetrahedronIndexs[12] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 3,
	1, 2, 3
};

GLfloat Figure::SquarePyramidVertexs[15] =
{
	0.0f, 0.5f, 0.0f,		// 꼭짓점
	-0.5f, -0.5f, -0.5f,	// 밑면
	-0.5f, -0.5f, 0.5f,		// 밑면
	0.5f, -0.5f, 0.5f,		// 밑면
	0.5f, -0.5f, -0.5f,		// 밑면
};

GLfloat Figure::SquarePyramidColors[15] =
{
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  //4번점
	0.0f, 0.0f, 1.0f,  //5번점
	0.0f, 0.0f, 0.0f,  //6번점
	1.0f, 0.0f, 0.0f,  //7번점
};

GLint Figure::SquarePyramidIndexs[18] =
{
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 1,
	1, 2, 3,
	3, 4, 1
};

GLfloat Figure::ConeVertexs[SIZE_CONE_VERTEX] = { 0.0f };
GLfloat Figure::ConeColors[SIZE_CONE_VERTEX] = { 0.0f };
GLint Figure::ConeIndexs[SIZE_CONE_INDEX] = { 0.0f };

GLfloat Figure::SqhereVertexs[SIZE_SQHERE_VERTEX] = { 0.0f };
GLfloat Figure::SqhereColors[SIZE_SQHERE_VERTEX] = { 0.0f };
GLint Figure::SqhereIndexs[SIZE_SQHERE_INDEX] = { 0 };