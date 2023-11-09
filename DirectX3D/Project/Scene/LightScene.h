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

	void CreateObject();

private:
	Quad* _floor;
	Quad* _floor2;

	Groot* _groot;

	Model* _bunny;

	Sphere* _sphere;

	DepthStencil* _depthStencil;
	RenderTarget* _renderTarget;

	FloatValueBuffer* _buffer;

};