#pragma once
#include "pch.h"

struct OBB {
	vec3 center;       // OBB �߽�
	vec3 halfSize;     // OBB ũ���� ��
	mat4 orientation;  // OBB ȸ�� ��Ʈ����
};

