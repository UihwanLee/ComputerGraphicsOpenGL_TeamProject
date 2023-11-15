#include "pch.h"

#define SIZE_CONE_VERTEX 66
#define SIZE_CONE_INDEX 60

#define SIZE_SQHERE_VERTEX 1323
#define SIZE_SQHERE_INDEX 2400

#define CONE_HEIGHT 1.0
#define RADIUS 0.7
#define STACKS 20
#define SLICES 20
#define PI 3.1415926535

class Figure
{
public:
	// ��ǥ���
	static GLfloat	CoordinateVertexs[18];
	static GLfloat	CoordinateColors[18];

	// ������ü
	static GLfloat	CubeVertexs[24];
	static GLfloat	CubeColors[24];
	static GLint	CubeIndexs[36];

	// �����ü
	static GLfloat	TetrahedronVertexs[12];
	static GLfloat	TetrahedronColors[12];
	static GLint	TetrahedronIndexs[12];

	// ���簢��
	static GLfloat	SquarePyramidVertexs[15];
	static GLfloat	SquarePyramidColors[15];
	static GLint	SquarePyramidIndexs[18];

	// ����
	static GLfloat	ConeVertexs[SIZE_CONE_VERTEX];
	static GLfloat	ConeColors[SIZE_CONE_VERTEX];
	static GLint	ConeIndexs[SIZE_CONE_INDEX];

	// ��
	static GLfloat	SqhereVertexs[SIZE_SQHERE_VERTEX];
	static GLfloat	SqhereColors[SIZE_SQHERE_VERTEX];
	static GLint	SqhereIndexs[SIZE_SQHERE_INDEX];
};
