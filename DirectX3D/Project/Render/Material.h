#pragma once
class Material
{
public:
	Material();
	Material(wstring file);
	~Material();

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);

	void SetShader(wstring file);

	void SetMaterial();

private:
	VertexShader* _vertexShader = nullptr;
	PixelShader* _pixelShader = nullptr;
};