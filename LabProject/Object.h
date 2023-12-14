#pragma once

#include "pch.h"
#include "Types.h"


class Object
{
public:
	Object();
	~Object();

	void BlickAnimation(float elapsedTime);
	void RayCasting();

	bool OBBIntersect(vec3 position);

	void SetPosition(vec3 position);
	void SetRotate(vec3 rotate);
	void SetScale(vec3 scale);
	void SetType(ObjectType type);
	void SetClose(bool close);
	void Setid(int id);

	OBB			GetObb();
	ObjectType	GetType();
	vec3		GetPosition();

	vec3		GetSize();

	void Update(float elapsedTime, vec3 position, bool& collision);
	void Render(class Renderer* renderer, class CameraController* cameracontroller);
public:
	OBB			m_obb;
	vec3		m_position;
	vec3		m_rotate;
	vec3		m_scale;

	ObjectType	m_type;
	bool		m_close;
	int			m_id;

	// ===========================
public:

	highp_vec3				m_colors;

	vector<unsigned int>	vertexIndices, uvIndices, normalIndices;
	vector<glm::vec3>		temp_vertices;
	vector<glm::vec2>		temp_uvs;
	vector<glm::vec3>		temp_normals;

	vector<glm::vec3>		m_vertices;
	vector<glm::vec2>		m_uvs;
	vector<glm::vec3>		m_normals;

	int						m_DRAW_TYPE;
	glm::mat4				m_model;

	bool					m_bActive;

	void SetPosition(float x, float y, float z);
	void SetRotate(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetActive(bool bActive);

	void Move(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	void GetBBMin(float* x, float* y, float* z);
	void GetBBMax(float* x, float* y, float* z);

	void ChangeType(ObjectType type);

	bool LoadMeshInfoFromFile(const char* file_name);

};
