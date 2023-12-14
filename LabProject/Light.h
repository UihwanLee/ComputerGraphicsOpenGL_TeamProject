#pragma once
#include "Camera.h"

class Light
{
public:
	Light();
	~Light();

	vec3 GetAttenuation();

	void SetLightPos(vec3 lightpos);
	void SetLightColor(vec3 lightColor);
	void SetView(vec3 camerapositon);
	vec3 GetLightPos() const;
	vec3 GetLightColor() const;
	vec3 GetLightviewPos() const;

private:
	vec3 m_lightPos = vec3{ 0.f };
	vec3 m_lightColor = vec3{ 0.f };
	vec3 m_lightviewPos = vec3{ 0.f };

};

