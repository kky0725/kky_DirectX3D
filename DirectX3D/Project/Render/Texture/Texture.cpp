#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::_textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:_srv(srv), _image(move(image))
{
	
}

Texture::~Texture()
{
	_srv->Release();
}

Texture* Texture::Get(wstring file)
{
	if (_textures.count(file) > 0)
		return _textures[file];

	file = L"_Texture/" + file;

	ScratchImage image;
	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);
	
	_textures[file] = new Texture(srv, image);

	return _textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : _textures)
		delete pair.second;

	_textures.clear();
}

void Texture::PSSetShaderResources(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &_srv);
}

