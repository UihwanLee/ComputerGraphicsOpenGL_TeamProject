#include "pch.h"
#include "Renderer.h"
#include "KeyBoard.h"
#include "CameraController.h"
#include "Light.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);



	vector<float> vertices;
	model.LoadFromFile("Obj\\Cube.obj");
	vertices = model.GetVertexData();
	vertexCount = model.GetVertexCount();

	glGenBuffers(1, &objVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	vertices.clear();

	model.LoadFromRinty("Obj\\Rinty.obj");
	vertices = model.GetVertexData();
	vertexCountRinty = model.GetVertexCount();

	glGenBuffers(1, &objRinty);
	glBindBuffer(GL_ARRAY_BUFFER, objRinty);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	vertices.clear();

	model.LoadFromRinty("Obj\\Flashlight.obj");
	vertices = model.GetVertexData();
	vertexCountFlash = model.GetVertexCount();

	glGenBuffers(1, &objFlash);
	glBindBuffer(GL_ARRAY_BUFFER, objFlash);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);


	InitTexture();
	InitShaderLocation();
	cutoff = vec2(10.f, 5.f);
}

Renderer::~Renderer()
{
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}


void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	shaderProgramID = CompileShaders("Shader\\vertex.glsl", "Shader\\fragment.glsl");

	if (shaderProgramID > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::ReadFile(const char* filename, std::string* target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

GLuint Renderer::CompileShaders(const char* filenameVS, const char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

void Renderer::ConvertToOpenGL(int x, int y, float* ox, float* oy)
{
	int w = m_WindowSizeX;
	int h = m_WindowSizeY;

	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

void Renderer::InitTexture()
{
	int width[6], height[6], numberOfChannel;
	unsigned char* textureData[6];

	stbi_set_flip_vertically_on_load(true);
	textureData[0] = stbi_load("Texture\\wall_texture.jfif", &width[0], &height[0], &numberOfChannel, 0);
	textureData[1] = stbi_load("Texture\\Stone.png", &width[1], &height[1], &numberOfChannel, 0);
	textureData[2] = stbi_load("Texture\\Prop.png", &width[2], &height[2], &numberOfChannel, 0);
	textureData[3] = stbi_load("Texture\\door.jpg", &width[3], &height[3], &numberOfChannel, 0);

	glGenTextures(4, m_CubeTexture);
	for (int i = 0; i < 4; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, m_CubeTexture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, textureData[i]);
		stbi_image_free(textureData[i]);
	}
}

void Renderer::InitShaderLocation()
{
	glUseProgram(shaderProgramID);

	AttributePosition = glGetAttribLocation(shaderProgramID, "vPos");
	glEnableVertexAttribArray(AttributePosition);
	AttributeNormal = glGetAttribLocation(shaderProgramID, "vNormal");
	glEnableVertexAttribArray(AttributeNormal);
	AttributeTexutre = glGetAttribLocation(shaderProgramID, "vTexCoord");
	glEnableVertexAttribArray(AttributeTexutre);

	modelMat = glGetUniformLocation(shaderProgramID, "modelTransform");
	viewMat = glGetUniformLocation(shaderProgramID, "viewTransform");
	projMat = glGetUniformLocation(shaderProgramID, "projectionTransform");
	pLightPos = glGetUniformLocation(shaderProgramID, "lightPos");
	pLightColor = glGetUniformLocation(shaderProgramID, "lightColor");
	pViewPos = glGetUniformLocation(shaderProgramID, "viewPos");
	atten = glGetUniformLocation(shaderProgramID, "attenuation");
	lightdirection = glGetUniformLocation(shaderProgramID, "lightdirection");
	lightcutoff = glGetUniformLocation(shaderProgramID, "lightcutoff");
	fTexture = glGetUniformLocation(shaderProgramID, "outTexture");
}

void Renderer::DrawCubeObj(CameraController* m_cameraController, vec3 position, vec3 rotate, vec3 size, ObjectType type)
{

	glBindBuffer(GL_ARRAY_BUFFER, objVBO);
	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 0));
	glVertexAttribPointer(AttributeTexutre, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 5));


	vec3 lightdirecon = m_cameraController->GetCameraFront();
	glUniform3fv(lightdirection, 1, glm::value_ptr(lightdirecon));

	glUniformMatrix4fv(viewMat, 1, GL_FALSE,
		glm::value_ptr(m_cameraController->GetViewMatrix()));

	glm::mat4 m_proj = perspective(glm::radians(45.0f), static_cast<float>(1200 / 600), 0.1f, 400.0f);
	glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(m_proj));

	Light* light = m_cameraController->GetLight();
	glUniform3f(pLightPos, light->GetLightPos().x, light->GetLightPos().y, light->GetLightPos().z);
	glUniform3f(pLightColor, light->GetLightColor().x, light->GetLightColor().y, light->GetLightColor().z);
	glUniform3f(pViewPos, light->GetLightviewPos().x, light->GetLightviewPos().y, light->GetLightviewPos().z);

	vec3 attenuation = light->GetAttenuation();
	glUniform3fv(atten, 1, glm::value_ptr(attenuation));

	glUniform2fv(lightcutoff, 1, glm::value_ptr(vec2(
		glm::cos(glm::radians(cutoff[0])),
		glm::cos(glm::radians(cutoff[0] + cutoff[1]))
	)));




	glUniform1i(fTexture, 0);
	glActiveTexture(GL_TEXTURE0);
	if (type == ObjectType::Cube) {
		glBindTexture(GL_TEXTURE_2D, m_CubeTexture[0]);
	}
	else if (type == ObjectType::Stone) {
		glBindTexture(GL_TEXTURE_2D, m_CubeTexture[1]);
	}
	else if (type == ObjectType::Prop) {
		glBindTexture(GL_TEXTURE_2D, m_CubeTexture[2]);
	}
	else if (type == ObjectType::Door) {
		glBindTexture(GL_TEXTURE_2D, m_CubeTexture[3]);
	}

	glm::mat4 m_model(1.0f);
	m_model = glm::translate(m_model, position);
	m_model = glm::scale(m_model, size);
	glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(m_model));
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Renderer::DrawRintyObj(CameraController* m_cameraController, vec3 position, vec3 rotate, vec3 size, float radian)
{

	glBindBuffer(GL_ARRAY_BUFFER, objRinty);
	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 0));
	glVertexAttribPointer(AttributeTexutre, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 5));

	vec3 lightdirecon = m_cameraController->GetCameraFront();
	glUniform3fv(lightdirection, 1, glm::value_ptr(lightdirecon));

	glUniformMatrix4fv(viewMat, 1, GL_FALSE,
		glm::value_ptr(m_cameraController->GetViewMatrix()));

	glm::mat4 m_proj = perspective(glm::radians(45.0f), static_cast<float>(1200 / 600), 0.1f, 400.0f);
	glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(m_proj));

	Light* light = m_cameraController->GetLight();
	glUniform3f(pLightPos, light->GetLightPos().x, light->GetLightPos().y, light->GetLightPos().z);
	glUniform3f(pLightColor, light->GetLightColor().x, light->GetLightColor().y, light->GetLightColor().z);
	glUniform3f(pViewPos, light->GetLightviewPos().x, light->GetLightviewPos().y, light->GetLightviewPos().z);

	vec3 attenuation = light->GetAttenuation();
	glUniform3fv(atten, 1, glm::value_ptr(attenuation));

	glUniform2fv(lightcutoff, 1, glm::value_ptr(vec2(
		glm::cos(glm::radians(cutoff[0])),
		glm::cos(glm::radians(cutoff[0] + cutoff[1]))
	)));


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform1i(fTexture, 0);
	glActiveTexture(GL_TEXTURE0);
	glm::mat4 m_model(1.0f);
	m_model = glm::translate(m_model, position);
	m_model = glm::rotate(m_model, radians(radian), rotate);
	m_model = glm::scale(m_model, size);
	glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(m_model));
	glDrawArrays(GL_TRIANGLES, 0, vertexCountRinty);
}

void Renderer::DrawFlashObj(CameraController* m_cameraController, vec3 position, vec3 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, objFlash);
	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 0));
	glVertexAttribPointer(AttributeTexutre, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 5));

	vec3 lightdirecon = m_cameraController->GetCameraFront();
	glUniform3fv(lightdirection, 1, glm::value_ptr(lightdirecon));

	glUniformMatrix4fv(viewMat, 1, GL_FALSE,
		glm::value_ptr(m_cameraController->GetViewMatrix()));

	glm::mat4 m_proj = perspective(glm::radians(45.0f), static_cast<float>(1200 / 600), 0.1f, 400.0f);
	glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(m_proj));

	Light* light = m_cameraController->GetLight();
	glUniform3f(pLightPos, light->GetLightPos().x, light->GetLightPos().y, light->GetLightPos().z);
	glUniform3f(pLightColor, light->GetLightColor().x, light->GetLightColor().y, light->GetLightColor().z);
	glUniform3f(pViewPos, light->GetLightviewPos().x, light->GetLightviewPos().y, light->GetLightviewPos().z);

	vec3 attenuation = light->GetAttenuation();
	glUniform3fv(atten, 1, glm::value_ptr(attenuation));

	glUniform2fv(lightcutoff, 1, glm::value_ptr(vec2(
		glm::cos(glm::radians(cutoff[0])),
		glm::cos(glm::radians(cutoff[0] + cutoff[1]))
	)));


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform1i(fTexture, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_CubeTexture[0]);
	glm::mat4 m_model(1.0f);
	m_model = glm::translate(m_model, position);

	m_model = glm::rotate(m_model, radians(10.f), vec3(0.f, 1.f, 0.f));
	m_model = glm::rotate(m_model, radians(20.f), vec3(1.f, 0.f, 0.f));
	m_model = glm::rotate(m_model, radians(180.f), vec3(0.f, 1.f, 0.f));
	m_model = glm::scale(m_model, size);
	glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(m_model));
	glDrawArrays(GL_TRIANGLES, 0, vertexCountFlash);
}