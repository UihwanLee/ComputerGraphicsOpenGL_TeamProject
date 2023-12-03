#include "pch.h"
#include "Light.h"

Light::Light() {

}

Light::~Light() {

}

void Light::SetLightPos(vec3 lightpos) {
	m_lightPos = lightpos;
}
void Light::SetLightColor(vec3 lightColor) {
	m_lightColor = lightColor;
}
void Light::SetView(vec3 cameraposition) {
	m_lightviewPos = cameraposition;
}

vec3 Light::GetLightPos() const { return m_lightPos; }
vec3 Light::GetLightColor() const { return m_lightColor; }
vec3 Light::GetLightviewPos() const { return m_lightviewPos; }