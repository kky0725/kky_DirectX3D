#pragma once
class ModelAnimationScene : public Scene
{
public:
	ModelAnimationScene();
	~ModelAnimationScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Groot* _groot;
	Terrain* _terrain;
	Quad* _crossHair;
	Sky* _sky;
	//SkyBox* _sky;
};