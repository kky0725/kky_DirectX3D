#pragma once
class Texture
{
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Get(wstring file);
	static Texture* Get(wstring key, ID3D11ShaderResourceView* srv);
	static Texture* Load(wstring file);

	static void Delete();

	void PSSetShaderResources(UINT slot);

	vector<Vector4> ReadPixels();

	Vector2 GetSize() { return Vector2(_image.GetMetadata().width, _image.GetMetadata().height); }
	wstring GetPath() { return _path; }

	ID3D11ShaderResourceView* GetSRV() { return _srv; }

private:
	ID3D11ShaderResourceView* _srv = nullptr;

	ScratchImage _image;

	static map<wstring, Texture*> _textures;

	wstring _path;

	bool _isReferred = false;
};