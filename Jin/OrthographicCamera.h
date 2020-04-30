#pragma once
#include "pch.h"
#include "Camera.h"

class OrthographicCamera : public Camera
{
    public:
	OrthographicCamera(f32 width, f32 height);
    
	
	virtual void Tick() override;
};

