#pragma once
class WaterScene : public Scene
{
public:
	WaterScene();
	virtual ~WaterScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void CreateObject();

private:
	Quad* _floor;
	Groot* _groot;
	Model* _bunny;
	Sphere* _sphere;

	Reflection* _reflection;
	Refraction* _refraction;
	Water* _water;

	SkyBox* _sky;

	Shadow* _shadow;
};