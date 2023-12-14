#include "pch.h"
#include "Light.h"

Light::Light() {

}

Light::~Light() {

}

vec3 Light::GetAttenuation()
{
	float distance = 300.f;
	const auto linear_coeff = glm::vec4(
		8.4523112e-05,
		4.4712582e+00,
		-1.8516388e+00,
		3.3955811e+01
	);
	const auto quad_coeff = glm::vec4(
		-7.6103583e-04,
		9.0120201e+00,
		-1.1618500e+01,
		1.0000464e+02
	);

	float kc = 1.0f;
	float d = 1.0f / distance;
	auto dvec = glm::vec4(1.0f, d, d * d, d * d * d);
	float kl = glm::dot(linear_coeff, dvec);
	float kq = glm::dot(quad_coeff, dvec);

	vec3 attenuation = glm::vec3(kc, glm::max(kl, 0.0f), glm::max(kq * kq, 0.0f));
	return attenuation;
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