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
	void SetDiffuseMap(Texture* texture);
	void SetSpecularMap(wstring file);
	void SetNormalMap(wstring file);

	MaterialBuffer* GetBuffer() { return _buffer; }

	void Debug();
	void SeletMap();

	void Save(wstring file);
	void Load(wstring file);

	void SaveMap(wstring file);
	void LoadMap(wstring file);

	void SaveDialog();
	void LoadDialog();

	void SaveMapDialog();
	void LoadMapDialog();

	void SetLabel(string label) { this->_label = label; }

	string GetLabel() { return _label; }


	Texture* GetDiffuseMap() { return _diffuseMap; }

private:
	VertexShader* _vertexShader = nullptr;
	PixelShader* _pixelShader = nullptr;

	Texture* _diffuseMap = nullptr;
	Texture* _specularMap = nullptr;
	Texture* _normalMap = nullptr;

	MaterialBuffer* _buffer = nullptr;

	string _projectDir;
	
	static int _ID;

	string _label = "";
};