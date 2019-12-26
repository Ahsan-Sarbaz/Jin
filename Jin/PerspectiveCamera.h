#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(int width, int height, int far, int near, int fov);

	virtual void Tick() override;
};

