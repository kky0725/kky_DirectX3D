#pragma once
class LightScene : public Scene
{
public:
	LightScene();
	virtual ~LightScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Quad* _floor;

	Groot* _groot;

	Model* _bunny;

	Sphere* _sphere;

};