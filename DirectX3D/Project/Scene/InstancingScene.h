#pragma once
class InstancingScene : public Scene
{
	struct InstanceData
	{
		Matrix Transform;

		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
public:
	InstancingScene();
	~InstancingScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	//vector<Quad*> _quads;
	Quad* _quad;

	const UINT COUNT = 50;

	vector<InstanceData> _instanceData;

	VertexBuffer* _instanceBuffer;

};