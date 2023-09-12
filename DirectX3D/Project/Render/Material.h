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

	void SetDiffuseMap(wstring file);
	void SetSpecularMap(wstring file);
	void SetNormalMap(wstring file);

	MaterialBuffer* GetBuffer() { return _buffer; }

	void PostRender();
	void SeletMap();

private:
	VertexShader* _vertexShader = nullptr;
	PixelShader* _pixelShader = nullptr;

	Texture* _diffuseMap = nullptr;
	Texture* _specularMap = nullptr;
	Texture* _normalMap = nullptr;

	MaterialBuffer* _buffer = nullptr;

	string _projectDir;
	
	static string _ID;
};