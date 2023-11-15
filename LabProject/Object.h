#include "pch.h"

class Object
{
public:
	float		m_pivot[3];
	float		m_rotate[3];
	float		m_scale[3];

	glm::mat4	m_model;

public:
	Object();
	~Object();

	void SetPosition(int idx, float x, float y, float z);
	void SetRotate(int idx, float x, float y, float z);
	void SetScale(int idx, float x, float y, float z);
	void SetActive(int idx, bool bActive);

	void Move(int idx, float x, float y, float z);
	void Rotate(int idx, float x, float y, float z);
	void Scale(int idx, float x, float y, float z);

private:

};
