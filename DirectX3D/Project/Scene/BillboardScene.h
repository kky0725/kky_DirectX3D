#pragma once
class BillboardScene : public Scene
{
public:
	BillboardScene();
	~BillboardScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	vector<Quad*> _trees;

	Terrain* _terrain;
};