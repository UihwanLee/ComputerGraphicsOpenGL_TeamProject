#include "pch.h"

#pragma once
class Object
{
public:
	vec3					m_position;
	vec3					m_rotate;
	vec3					m_scale;

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

public:
	Object();
	~Object();

	void SetPosition(float x, float y, float z);
	void SetRotate(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetActive(bool bActive);

	void Move(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	bool LoadMeshInfoFromFile(const char* file_name);

};
