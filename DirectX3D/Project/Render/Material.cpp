#include "Framework.h"
#include "Material.h"

Material::Material()
{
	_buffer = new MaterialBuffer();
}

Material::Material(wstring file)
{
	SetShader(file);
	_buffer = new MaterialBuffer();
}

Material::~Material()
{
	delete _buffer;
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

	if (_specularMap)
		_specularMap->PSSetShaderResources(1);

	if (_normalMap)
		_normalMap->PSSetShaderResources(2);

	_buffer->SetPSBuffer(1);
}

void Material::SetDiffuseMap(wstring file)
{
	_diffuseMap = Texture::Get(file);
	_buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	_specularMap = Texture::Get(file);
	_buffer->data.hasSpecularMap = true;
}

void Material::SetNormalMap(wstring file)
{
	_normalMap = Texture::Get(file);
	_buffer->data.hasNormalMap = true;
}

void Material::PostRender()
{
	ImGui::ColorEdit4("Diffuse", (float*)&_buffer->data.diffuse);
	ImGui::ColorEdit4("Specular", (float*)&_buffer->data.specular);
	ImGui::ColorEdit4("Ambient", (float*)&_buffer->data.ambinet);

	ImGui::Checkbox("HasDiffuseMap", (bool*)&_buffer->data.hasDiffuseMap);
	ImGui::Checkbox("HasSpecularMap", (bool*)&_buffer->data.hasSpecularMap);
	ImGui::Checkbox("HasNormalMap", (bool*)&_buffer->data.hasNormalMap);

	ImGui::SliderFloat("Shininess", &_buffer->data.shininess, 1.0f, 50.0f);
}


