#pragma once
#include <map>

class OBJModel
{
public:
	OBJModel();
	~OBJModel();

	void LoadFromFile(const char* fileName);
	void LoadFromRinty(const char* fileName);
	vector<float> GetVertexData();
	int GetVertexCount();

private:
	struct Position { float x, y, z; };
	struct Texture { float x, y; };
	struct Normal { float x, y, z; };
	struct Color { float r, g, b; };

	void LoadMaterialFile(const char* fileName);
	bool StartWith(string& line, const char* text);
	void AddVertexData(int vIdx, int tIdx, int nIdx, const char* mtl,
		vector<Position>& vertices, vector<Texture>& textures, vector<Normal>& normals);
	void AddVertexDataRinty(int vIdx, int tIdx, int nIdx, const char* mtl,
		vector<Position>& vertices, vector<Texture>& textures, vector<Normal>& normals);

	map<string, Color> mMaterailMap;

	vector<float> mVertexData;
};

