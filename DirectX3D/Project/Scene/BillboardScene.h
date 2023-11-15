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
	//vector<Quad*> _trees;

	Terrain* _terrain;

	VertexBuffer*	_vertexBuffer;
	Material*		_material;
	GeometryShader* _geometryShader;

	vector<VertexTexture> _vertices;
	//vector<VertexTexture> _drawVertices;

	const UINT COUNT = 1000;
	UINT _drawCount = COUNT;

};