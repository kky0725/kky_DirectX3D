#include "Framework.h"
#include "Material.h"

Material::Material()
{
}

Material::Material(wstring file)
{
	SetShader(file);
}

Material::~Material()
{
}

void Material::SetVertexShader(wstring file)
{
	_vertexShader = Shader::GetVS(file);
}

void Material::SetPixelShader(wstring file)
{
	_pixelShader = Shader::GetPS(file);
}

void Material::SetShader(wstring file)
{
	SetVertexShader(file);
	SetPixelShader(file);
}

void Material::SetMaterial()
{
	_vertexShader->SetShader();
	_pixelShader->SetShader();

	if (_diffuseMap)
		_diffuseMap->PSSetShaderResources(0);
}

void Material::SetDiffuseMap(wstring file)
{
	_diffuseMap = Texture::Get(file);
}


