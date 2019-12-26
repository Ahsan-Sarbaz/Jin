#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera
{	
public:
	OrthographicCamera(int width, int height);

	
	virtual void Tick() override;
};

