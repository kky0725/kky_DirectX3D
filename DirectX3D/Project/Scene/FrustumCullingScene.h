#pragma once
class FrustumCullingScene : public Scene
{
public:
	FrustumCullingScene();
	~FrustumCullingScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	vector<Sphere*> _spheres;

	const UINT SIZE = 10;
	UINT _drawCount = 0;

};