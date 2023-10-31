#pragma once
class Sky
{
public:
	Sky();
	~Sky();
	
	void Render();
	void PostRender();

private:
	Sphere* _sphere;
	RasterizerState* _rs;
	SkyBuffer* _buffer;
};