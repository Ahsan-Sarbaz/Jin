#pragma once
class Layer
{
private:
	const char* m_name;
public:
	Layer(const char* name);
	
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

	const char* GetName() const { return m_name; }
};