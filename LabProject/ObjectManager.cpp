#include "pch.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(GLuint shaderProgramID)
{
	m_shaderProgramID = shaderProgramID;
	m_ObjectList.clear();
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < m_ObjectList.size(); i++)
	{
		delete m_ObjectList[i];
	}
}

int ObjectManager::GetRandomIntValue(GLfloat min, GLfloat max)
{
	GLfloat value;

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<GLfloat> dis(min, max);

	value = dis(gen);

	return int(value);
}

GLfloat ObjectManager::GetRandomFloatValue(GLfloat min, GLfloat max)
{
	GLfloat value;

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<GLfloat> dis(min, max);

	value = dis(gen);

	return value;
}

void ObjectManager::CreateFigure(Object* gameObject, highp_vec3 color)
{
	// vertexs
	for (unsigned int i = 0; i < gameObject->vertexIndices.size(); i++) {
		unsigned int vertexIndex = gameObject->vertexIndices[i];
		glm::vec3 vertex = gameObject->temp_vertices[vertexIndex - 1];
		gameObject->m_vertices.push_back(vertex);
	}

	// uvs
	for (unsigned int i = 0; i < gameObject->uvIndices.size(); i++) {
		unsigned int uvIndex = gameObject->uvIndices[i];
		glm::vec2 uv = gameObject->temp_uvs[uvIndex - 1];
		gameObject->m_uvs.push_back(uv);
	}

	// normals
	for (unsigned int i = 0; i < gameObject->normalIndices.size(); i++) {
		unsigned int normalIndex = gameObject->normalIndices[i];
		glm::vec3 normal = gameObject->temp_normals[normalIndex - 1];
		gameObject->m_normals.push_back(normal);
	}

	gameObject->m_colors.r = color.r; gameObject->m_colors.g = color.g; gameObject->m_colors.b = color.b;

	gameObject->m_DRAW_TYPE = GL_TRIANGLES;

	gameObject->m_bActive = true;

	m_ObjectList.emplace_back(gameObject);
}

void ObjectManager::CreateCube(int* idx, highp_vec3 color, ObjectType type)
{
	*idx += 1;

	Object* gameObject = new Object();

	gameObject->LoadMeshInfoFromFile("cube.txt");
	gameObject->m_type = type;

	CreateFigure(gameObject, color);
}

void ObjectManager::CreateSqhere(int* idx, highp_vec3 color, ObjectType type)
{
	*idx += 1;
}

void ObjectManager::SetPosition(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->SetPosition(x, y, z);
}

void ObjectManager::SetRotate(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->SetRotate(x, y, z);
}

void ObjectManager::SetScale(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->SetScale(x, y, z);
}

void ObjectManager::SetActive(int idx, bool bActive)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->SetActive(bActive);
}

void ObjectManager::Move(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->Move(x, y, z);
}

void ObjectManager::Rotate(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->Rotate(x, y, z);
}

void ObjectManager::Scale(int idx, float x, float y, float z)
{
	if (m_ObjectList.empty()) return;

	m_ObjectList[idx]->Scale(x, y, z);
}

glm::mat4 ObjectManager::TransformModel(int idx)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 move = glm::mat4(1.0f);

	if (!m_ObjectList.empty())
	{
		float scale_x_parent; float scale_y_parent; float scale_z_parent;
		float move_x_parent; float move_y_parent; float move_z_parent;
		float rotate_y_parent;

		float move_x = m_ObjectList[idx]->m_position.x;
		float move_y = m_ObjectList[idx]->m_position.y;
		float move_z = m_ObjectList[idx]->m_position.z;

		float rotate_x = m_ObjectList[idx]->m_rotate.x;
		float rotate_y = m_ObjectList[idx]->m_rotate.y;
		float rotate_z = m_ObjectList[idx]->m_rotate.z;

		float scale_x = m_ObjectList[idx]->m_scale.x;
		float scale_y = m_ObjectList[idx]->m_scale.y;
		float scale_z = m_ObjectList[idx]->m_scale.z;

		model = glm::mat4(1.0f);

		// 기본 Transform
		model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));
		model = glm::rotate(model, glm::radians(rotate_x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(move_x, move_y, move_z));

		// IDX에 따라 Transform을 달리 해준다.

		// Picking 상태이면 Camera Transform을 따라감

		// glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
	}

	return model;
}
