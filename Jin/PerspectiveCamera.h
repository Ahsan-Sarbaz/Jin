#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(int width, int height, float near, int far, int fov);

	virtual void Tick() override;
};

