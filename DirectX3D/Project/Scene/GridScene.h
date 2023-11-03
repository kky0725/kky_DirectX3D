#pragma once
class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();
	
	virtual void Update() override;
	
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateMesh();


private:
	int _width = 100, _height = 100;

	Material* _material;

	VertexBuffer* _vertexBuffer;

	vector<VertexColor> _vertices;

	WorldBuffer* _worldBuffer;
};