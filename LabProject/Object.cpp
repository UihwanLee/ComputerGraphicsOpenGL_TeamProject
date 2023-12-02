#include "pch.h"
#include "Object.h"

Object::Object()
{
	m_position.x = 0.0f; m_position.y = 0.0f; m_position.z = 0.0f;
	m_rotate.x = 0.0f; m_rotate.y = 0.0f; m_rotate.z = 0.0f;
	m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f;

	m_model = glm::mat4(1.0f);

	m_type = ObjectType::DEFAULT;

	m_bActive = true;
}

Object::~Object()
{
}

void Object::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Object::SetRotate(float x, float y, float z)
{
	m_rotate.x = x;
	m_rotate.y = y;
	m_rotate.z = z;
}

void Object::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Object::SetActive(bool bActive)
{
	m_bActive = bActive;
}


void Object::Move(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}


void Object::Rotate(float x, float y, float z)
{
	if (x != 0.0f) m_rotate.x += x;
	else if (y != 0.0f)  m_rotate.y += y;
	else if (z != 0.0f)  m_rotate.z += z;
}

void Object::Scale(float x, float y, float z)
{
	m_scale.x += x;
	m_scale.y += y;
	m_scale.z += z;
}

bool Object::LoadMeshInfoFromFile(const char* file_name)
{
	char bind[128];

	FILE* file;
	fopen_s(&file, file_name, "r");

	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (!feof(file)) {

		// read the first word of the line
		fscanf_s(file, "%s", bind, sizeof(bind));

		if (bind[0] == 'v' && bind[1] == '\0') {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		if ((bind[0] == 'v' && bind[1] == 't' && bind[2] == '\0')) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		if ((bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0')) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		if (bind[0] == 'f' && bind[1] == '\0') {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	return true;
}