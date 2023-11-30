#include "pch.h"
#include "Light.h"

Light::Light()
{
	mPosition = vec3(0.f);
	mYaw = 0.f;
	mPitch = 0.f;

	mColor = highp_vec3(0.8f);
}

Light::~Light()
{
}

vec3 Light::GetPosition()
{
	return mPosition;
}

vec3 Light::GetForward()
{
	vec4 forward = inverse(GetRotationMatrix()) * vec4(0.f, 0.f, -1.f, 1.f);
	return vec3(forward);
}

vec3 Light::GetRight()
{
	vec4 right = inverse(GetRotationMatrix()) * vec4(1.f, 0.f, 0.f, 1.f);
	return vec3(right);
}

vec3 Light::GetUp()
{
	vec4 up = inverse(GetRotationMatrix()) * vec4(0.f, 1.f, 0.f, 1.f);
	return vec3(up);
}

mat4 Light::GetViewMatrix()
{
	return GetRotationMatrix() * translate(mat4(1.f), -mPosition);
}

mat4 Light::GetRotationMatrix()
{
	mat4 rotation(1.f);
	rotation = rotate(rotation, radians(mPitch), vec3(1.f, 0.f, 0.f));
	rotation = rotate(rotation, radians(mYaw), vec3(0.f, 1.f, 0.f));
	return rotation;
}

highp_vec3 Light::GetColor()
{
	return mColor;
}

void Light::Move(vec3 direction, float amount)
{
	direction.y = 0;
	mPosition = mPosition + direction * amount;
}

void Light::Yaw(float angle)
{
	mYaw += angle;
	NormalizeYaw();
}

void Light::Pitch(float angle)
{
	mPitch += angle;
	NormalizePitch();
}

void Light::TurnTo(vec3 position)
{
	if (position == mPosition) return;

	vec3 direction = normalize(position - mPosition);
	mPitch = degrees(asinf(-direction.y));
	NormalizePitch();

	mYaw = -degrees(atan2f(-direction.x, -direction.z));
	NormalizeYaw();
}

void Light::MoveTo(vec3 position)
{
	mPosition = position;
}

void Light::NormalizeYaw()
{
	mYaw = fmodf(mYaw, 360.f);
	if (mYaw < 0.f) {
		mYaw += 360.f;
	}
}

void Light::NormalizePitch()
{
	if (mPitch > 89.f)
		mPitch = 89.f;
	if (mPitch < -89.f)
		mPitch = -89.f;
}
