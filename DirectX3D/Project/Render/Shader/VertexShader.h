#pragma once
class VertexShader : public Shader
{
	friend class Shader;
	VertexShader(wstring file);
	~VertexShader();

public:
	virtual void SetShader() override;

private:
	void CreateInputLayOut();

private:
	ID3D11InputLayout*  _inputLayout;
	ID3D11VertexShader* _vertexShader;
};
