#pragma once
class TessellationScene : public Scene
{
public:
	TessellationScene();
	virtual ~TessellationScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Material* _material;

	HullShader* _hullShader;
	DomainShader* _domainShader;

	VertexBuffer* _vertexBuffer;

	vector<Vertex> _vertices;

	FloatValueBuffer* _edgeBuffer;
	FloatValueBuffer* _insideBuffer;
};