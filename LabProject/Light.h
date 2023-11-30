#pragma once
class Light
{
public:
	Light();
	~Light();

	vec3 GetPosition();
	vec3 GetForward();
	vec3 GetRight();
	vec3 GetUp();
	mat4 GetViewMatrix();
	mat4 GetRotationMatrix();
	highp_vec3 GetColor();

	void Move(vec3 direction, float amount);
	void Yaw(float angle);
	void Pitch(float angle);

	void TurnTo(vec3 position);
	void MoveTo(vec3 position);

private:
	void NormalizeYaw();
	void NormalizePitch();

	vec3 mPosition;
	float mYaw;			// 좌우 회전 각
	float mPitch;		// 상하 회전 각

	highp_vec3 mColor;
};

