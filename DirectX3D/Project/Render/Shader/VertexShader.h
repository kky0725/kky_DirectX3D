#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	virtual void SetShader() override;

private:
	void CreateInputLayOut();

private:
	ID3D11InputLayout*  _inputLayout;
	ID3D11VertexShader* _vertexShader;
};
