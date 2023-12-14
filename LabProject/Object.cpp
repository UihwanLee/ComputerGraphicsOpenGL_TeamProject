#include "pch.h"
#include "Object.h"
#include "Renderer.h"
#include "Global.h"

Object::Object()
{
	m_position = vec3(0.f);
	m_rotate = vec3(0.f);
	m_scale = vec3(1.f);
	m_type = ObjectType::None;
	m_close = true;

	m_obb.center = m_position;
	m_obb.halfSize = m_scale * vec3(0.5f, 0.5f, 0.5f);  // 예시 크기
	m_obb.orientation = glm::mat4(1.0f);  // 회전 없음

}

Object::~Object()
{
}

void Object::BlickAnimation(float elapsedTime)
{
	float move_speed = 250.f;
	m_position.z += elapsedTime * move_speed;
}

void Object::RayCasting()
{

}

bool Object::OBBIntersect(vec3 position)
{
	if (!m_close)
		return false;

	OBB cameraOBB;
	cameraOBB.center = position;
	cameraOBB.halfSize = glm::vec3(0.7f, 0.7f, 0.7f);
	cameraOBB.orientation = glm::mat4(1.0f);

	OBB cubeOBB;
	cubeOBB.center = m_position;

	if (m_type == ObjectType::Cube)
		cubeOBB.halfSize = m_scale * vec3(0.5f, 0.5f, 0.5f);
	else if (m_type == ObjectType::Rinty)
		cubeOBB.halfSize = m_scale * vec3(0.7f, 0.7f, 0.7f);
	else if (m_type == ObjectType::Prop) {
		cubeOBB.center.y = m_position.y + m_scale.y;
		cubeOBB.halfSize = m_scale * vec3(0.5f, 0.5f, 0.5f);
	}
	else if (m_type == ObjectType::Stone) {
		cubeOBB.halfSize = m_scale * vec3(0.7f, 0.7f, 0.7f);
	}
	else if (m_type == ObjectType::Door)
		cubeOBB.halfSize = m_scale * vec3(0.8f, 0.8f, 0.8f);

	cubeOBB.orientation = glm::mat4(1.0f);
	glm::vec3 distanceVector = cameraOBB.center - cubeOBB.center;
	// obb1 좌표 공간에서 obb2 좌표 공간으로 변환
	glm::mat4 obb1ToWorld = cubeOBB.orientation;
	glm::mat4 worldToObb2 = glm::inverse(cameraOBB.orientation);
	glm::vec3 distanceVectorTransformed = glm::vec3(worldToObb2 * obb1ToWorld * glm::vec4(distanceVector, 1.0f));

	for (int i = 0; i < 3; ++i) {
		glm::vec3 axis = glm::vec3(cubeOBB.orientation[i]);

		float obb1Projection = cubeOBB.halfSize[i];
		float obb2Projection = cameraOBB.halfSize.x * glm::abs(glm::dot(axis, glm::vec3(worldToObb2[i])));
		float totalProjection = obb1Projection + obb2Projection;

		if (glm::abs(distanceVectorTransformed[i]) > totalProjection) {
			return false;
		}
	}

	return true;
}

void Object::SetPosition(vec3 position)
{
	m_position = position;
	m_obb.center = m_position;

}

void Object::SetRotate(vec3 rotate)
{
	m_rotate = rotate;
}

void Object::SetScale(vec3 scale)
{
	m_scale = scale;
	m_obb.halfSize = m_scale * vec3(0.5f, 0.5f, 0.5f);
}

void Object::SetType(ObjectType type)
{
	m_type = type;
}

void Object::SetClose(bool close)
{
	m_close = close;
}

void Object::Setid(int id)
{
	m_id = id;
}

OBB Object::GetObb()
{
	return m_obb;
}

ObjectType Object::GetType()
{
	return m_type;
}

vec3 Object::GetPosition()
{
	return m_position;

}

vec3 Object::GetSize()
{
	return m_scale;

}


void Object::Update(float elapsedTime, vec3 position, bool& collision)
{

	static bool blickAnimation = false;

	switch (m_type)
	{
	case ObjectType::Cube:
	case ObjectType::Prop:
	case ObjectType::Rinty:
		if (OBBIntersect(position)) {
			collision = true;
		}
		break;
	case ObjectType::Stone:
		if (OBBIntersect(position)) {
			if (m_id == 46) {
				g_change = true;
			}
		}
		break;
	case ObjectType::Blink:
		if (blickAnimation) {
			BlickAnimation(elapsedTime);
		}
		if (position.z < -190.f && !blickAnimation) {
			blickAnimation = true;
		}
		if (m_position.z >= -10.f) {
			blickAnimation = false;
			m_position.z = -10.f;
		}
		break;
	}


}

void Object::Render(Renderer* renderer, CameraController* cameracontroller)
{
	if (!m_close)
		return;

	switch (m_type)
	{
	case ObjectType::Cube:
	case ObjectType::Prop:
	case ObjectType::Stone:
	case ObjectType::Door:
		if (m_close)
			renderer->DrawCubeObj(cameracontroller, m_position, m_rotate, m_scale, m_type);
		break;
	case ObjectType::Blink:
		renderer->DrawRintyObj(cameracontroller, m_position, m_rotate, m_scale, 0.f);
		break;
	case ObjectType::Rinty:
		renderer->DrawRintyObj(cameracontroller, m_position, m_rotate, m_scale, 90.f);
		break;
	default:
		break;
	}
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

void Object::GetBBMin(float* x, float* y, float* z)
{
	*x = m_position.x - m_scale.x / 2.f;
	*y = m_position.y - m_scale.y / 2.f;
	*z = m_position.z - m_scale.z / 2.f;
}

void Object::GetBBMax(float* x, float* y, float* z)
{
	*x = m_position.x + m_scale.x / 2.f;
	*y = m_position.y + m_scale.y / 2.f;
	*z = m_position.z + m_scale.z / 2.f;
}

void Object::ChangeType(ObjectType type)
{
	m_type = type;
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