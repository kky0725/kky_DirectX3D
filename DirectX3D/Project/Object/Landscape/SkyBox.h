#pragma once
class SkyBox
{
public:
	SkyBox(wstring file);
	~SkyBox();

	void Render();

private:
	Sphere* _sphere;

	RasterizerState* _rs;

	Texture* _cubeMap;
};