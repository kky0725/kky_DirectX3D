#pragma once
class Texture
{
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Get(wstring file);
	static void Delete();

	void PSSetShaderResources(UINT slot);

private:
	ID3D11ShaderResourceView* _srv = nullptr;

	ScratchImage _image;

	static map<wstring, Texture*> _textures;
};