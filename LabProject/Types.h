#pragma once
#include "pch.h"

struct OBB {
	vec3 center;       // OBB 중심
	vec3 halfSize;     // OBB 크기의 반
	mat4 orientation;  // OBB 회전 매트릭스
};

