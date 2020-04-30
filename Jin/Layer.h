#pragma once
#include "pch.h"

class Layer
{
    private:
	cstr m_name;
    
    public:
	Layer(cstr name);
	
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
    
	cstr GetName() const { return m_name; }
};