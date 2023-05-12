#pragma once
#include "Camera.h"

class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera();
	~PerspectiveCamera()override = default;

	void Setup(void) const override;

	void SetFov(float fov);

	PerspectiveCamera(const PerspectiveCamera&) = delete;
	PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;

	PerspectiveCamera(PerspectiveCamera&&) = default;
	PerspectiveCamera& operator=(PerspectiveCamera&&) = default;
private:
	float fov_;

};
