#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	vec3 GetPosition();
	vec3 GetForward();
	vec3 GetRight();
	vec3 GetUp();
	mat4 GetViewMatrix();
	mat4 GetRotationMatrix();

	vec3 GetRotate();

	vec3 TryMove(vec3 direction, float amount);
	void Move(vec3 direction, float amount);
	void Yaw(float angle);
	void Pitch(float angle);

	void TurnTo(vec3 position);
	void MoveTo(vec3 position);

private:
	void NormalizeYaw();
	void NormalizePitch();

	vec3 mPosition;
	float mYaw;			// �¿� ȸ�� ��
	float mPitch;		// ���� ȸ�� ��
};

