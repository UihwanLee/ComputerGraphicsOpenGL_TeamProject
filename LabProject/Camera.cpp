#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	mPosition = vec3(0.f);
	mYaw = 0.f;
	mPitch = 0.f;
}

Camera::~Camera()
{
}

vec3 Camera::GetPosition()
{
	return mPosition;
}

vec3 Camera::GetForward()
{
	vec4 forward = inverse(GetRotationMatrix()) * vec4(0.f, 0.f, -1.f, 1.f);
	return vec3(forward);
}

vec3 Camera::GetRight()
{
	vec4 right = inverse(GetRotationMatrix()) * vec4(1.f, 0.f, 0.f, 1.f);
	return vec3(right);
}

vec3 Camera::GetUp()
{
	vec4 up = inverse(GetRotationMatrix()) * vec4(0.f, 1.f, 0.f, 1.f);
	return vec3(up);
}

mat4 Camera::GetViewMatrix()
{
	return GetRotationMatrix() * translate(mat4(1.f), -mPosition);
}

mat4 Camera::GetRotationMatrix()
{
	mat4 rotation(1.f);
	rotation = rotate(rotation, radians(mPitch), vec3(1.f, 0.f, 0.f));
	rotation = rotate(rotation, radians(mYaw), vec3(0.f, 1.f, 0.f));
	return rotation;
}

vec3 Camera::TryMove(vec3 direction, float amount)
{
	direction.y = 0;
	return mPosition + direction * amount;
}

void Camera::Move(vec3 direction, float amount)
{
	direction.y = 0;
	mPosition = mPosition + direction * amount;
}

void Camera::Yaw(float angle)
{
	mYaw += angle;
	NormalizeYaw();
}

void Camera::Pitch(float angle)
{
	mPitch += angle;
	NormalizePitch();
}

void Camera::TurnTo(vec3 position)
{
	if (position == mPosition) return;

	vec3 direction = normalize(position - mPosition);
	mPitch = degrees(asinf(-direction.y));
	NormalizePitch();

	mYaw = -degrees(atan2f(-direction.x, -direction.z));
	NormalizeYaw();
}

void Camera::MoveTo(vec3 position)
{
	mPosition = position;
}

float Camera::GetYaw()
{
	return mYaw;
}

float Camera::GetPitch()
{
	return mPitch;
}

void Camera::NormalizeYaw()
{
	mYaw = fmodf(mYaw, 360.f);
	if (mYaw < 0.f) {
		mYaw += 360.f;
	}
}

void Camera::NormalizePitch()
{
	if (mPitch > 89.f)
		mPitch = 89.f;
	if (mPitch < -89.f)
		mPitch = -89.f;
}
