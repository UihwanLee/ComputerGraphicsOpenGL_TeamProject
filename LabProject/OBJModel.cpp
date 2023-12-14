#include "pch.h"
#include "OBJModel.h"

OBJModel::OBJModel() {

}

OBJModel::~OBJModel() {

}

void OBJModel::LoadFromFile(const char* fileName) {
	mVertexData.clear();

	vector<Position> vertices;
	vector<Texture> textures;
	vector<Normal> normals;

	ifstream file(fileName);
	if (file) {
		char currentMtlName[100];
		string line;
		while (getline(file, line)) {
			if (StartWith(line, "mtllib")) {
				char mtlFileName[100];
				(void)sscanf_s(line.c_str(), "mtllib %s", mtlFileName, sizeof(mtlFileName));
				//LoadMaterialFile(mtlFileName);
			}
			if (StartWith(line, "v ")) {
				Position pos;
				sscanf_s(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
				vertices.push_back(pos);
			}
			if (StartWith(line, "vn")) {
				Normal n;
				sscanf_s(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
				normals.push_back(n);
			}
			if (StartWith(line, "vt")) {
				Texture t;
				sscanf_s(line.c_str(), "vt %f %f", &t.x, &t.y);
				textures.push_back(t);
			}
			if (StartWith(line, "usemtl")) {
				(void)sscanf_s(line.c_str(), "usemtl %s", currentMtlName, sizeof(currentMtlName));
			}
			if (StartWith(line, "f ")) {
				int v1, v2, v3;
				int t1, t2, t3;
				int n1, n2, n3;
				(void)sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&v1, &t1, &n1,
					&v2, &t2, &n2,
					&v3, &t3, &n3);

				AddVertexData(v1, t1, n1, currentMtlName, vertices, textures, normals);
				AddVertexData(v2, t2, n2, currentMtlName, vertices, textures, normals);
				AddVertexData(v3, t3, n3, currentMtlName, vertices, textures, normals);
			}
		}
		int a = 4;
	}
	else {
		cout << "Obj File loading Fail!" << endl;
	}
}

void OBJModel::LoadFromRinty(const char* fileName)
{
	mVertexData.clear();

	vector<Position> vertices;
	vector<Texture> textures;
	vector<Normal> normals;

	ifstream file(fileName);
	if (file) {
		char currentMtlName[100];
		string line;
		while (getline(file, line)) {
			if (StartWith(line, "mtllib")) {
				char mtlFileName[100];
				(void)sscanf_s(line.c_str(), "mtllib %s", mtlFileName, sizeof(mtlFileName));
				//LoadMaterialFile(mtlFileName);
			}
			if (StartWith(line, "v ")) {
				Position pos;
				sscanf_s(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
				vertices.push_back(pos);
			}
			if (StartWith(line, "vn")) {
				Normal n;
				sscanf_s(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
				normals.push_back(n);
			}
			if (StartWith(line, "vt")) {
				Texture t;
				sscanf_s(line.c_str(), "vt %f %f", &t.x, &t.y);
				textures.push_back(t);
			}
			if (StartWith(line, "usemtl")) {
				(void)sscanf_s(line.c_str(), "usemtl %s", currentMtlName, sizeof(currentMtlName));
			}
			if (StartWith(line, "f ")) {
				int v1, v2, v3;
				int t1, t2, t3;
				int n1, n2, n3;
				(void)sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&v1, &t1, &n1,
					&v2, &t2, &n2,
					&v3, &t3, &n3);
				// v, t, n
				AddVertexDataRinty(v1, t1, n1, currentMtlName, vertices, textures, normals);
				AddVertexDataRinty(v2, t2, n2, currentMtlName, vertices, textures, normals);
				AddVertexDataRinty(v3, t3, n3, currentMtlName, vertices, textures, normals);
			}
		}
	}
	else {
		cout << "Obj File loading Fail!" << endl;
	}
}

vector<float> OBJModel::GetVertexData() {

	return mVertexData;
}

int OBJModel::GetVertexCount() {
	return mVertexData.size() / 8;
}

void OBJModel::LoadMaterialFile(const char* fileName) {
	ifstream file(fileName);

	if (file) {
		string line;
		while (getline(file, line)) {
			char mtlName[100];
			if (StartWith(line, "newmtl")) {
				(void)sscanf_s(line.c_str(), "newmtl %s", mtlName, sizeof(mtlName));
				mMaterailMap[mtlName] = Color();
			}
			if (StartWith(line, "Kd")) {
				Color& color = mMaterailMap[mtlName];
				sscanf_s(line.c_str(), "Kd %f %f %f", color.r, color.g, color.b);
			}
		}
	}
	else {
		cout << "Materail File loading Fail!" << endl;
	}
}

bool OBJModel::StartWith(string& line, const char* text) {
	size_t textlen = strlen(text);
	if (line.size() < textlen) {
		return false;
	}
	for (size_t i = 0; i < textlen; ++i) {
		if (line[i] == text[i])continue;
		else return false;
	}

	return true;
}

void OBJModel::AddVertexData(int vIdx, int tIdx, int nIdx, const char* mtl,
	vector<Position>& vertices, vector<Texture>& textures, vector<Normal>& normals) {

	Position p = vertices[vIdx - 1];
	Texture t = textures[tIdx - 1];
	Normal n = normals[nIdx - 1];

	mVertexData.push_back(p.x);
	mVertexData.push_back(p.y);
	mVertexData.push_back(p.z);
	mVertexData.push_back(t.x);
	mVertexData.push_back(t.y);
	mVertexData.push_back(n.x);
	mVertexData.push_back(n.y);
	mVertexData.push_back(n.z);
}

void OBJModel::AddVertexDataRinty(int vIdx, int tIdx, int nIdx, const char* mtl, vector<Position>& vertices, vector<Texture>& textures, vector<Normal>& normals)
{
	Position p = vertices[vIdx - 1];
	Texture t = textures[tIdx - 1];
	Normal n = normals[nIdx - 1];

	mVertexData.push_back(p.x);
	mVertexData.push_back(p.y);
	mVertexData.push_back(p.z);
	mVertexData.push_back(t.x);
	mVertexData.push_back(t.y);
	mVertexData.push_back(n.x);
	mVertexData.push_back(n.y);
	mVertexData.push_back(n.z);

}

