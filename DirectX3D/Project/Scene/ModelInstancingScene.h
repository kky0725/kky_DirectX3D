#pragma once
class ModelInstancingScene : public Scene
{
public:
	ModelInstancingScene();
	~ModelInstancingScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	ModelAnimatorInstancing* _model;

	int _instanceIndex = 0;
	int _clip = 0;
};