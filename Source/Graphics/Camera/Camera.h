#pragma once
#include <DxLib.h>

class Camera
{
public:
	Camera();
	virtual ~Camera() = default;

	virtual void Setup(void) const;

	void SetNearFar(float nearDis, float farDis);

	void SetPosition(const VECTOR& pos);

	void SetTarget(const VECTOR& target);

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	Camera(Camera&&) = default;
	Camera& operator=(Camera&&) = default;

private:
	float near_;
	float far_;

	VECTOR pos_;
	VECTOR target_;

};
