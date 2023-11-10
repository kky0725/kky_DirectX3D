#pragma once
class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene();
	virtual ~DeferredRenderScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateObject();
private:
	Quad*	_floor;
	Groot*	_groot;
	Model*	_bunny;
	Sphere* _sphere;

	GeomtryBuffer* _gBuffer;

	Material*		_material;
	VertexBuffer*	_vertexBuffer;
};