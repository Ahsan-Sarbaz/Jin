#pragma once
#include "pch.h"
#include "Camera.h"

class PerspectiveCamera : public Camera
{
    public:
	PerspectiveCamera(f32 width, f32 height, f32 near, f32 far, f32 fov);
    
	virtual void Tick() override;
};

