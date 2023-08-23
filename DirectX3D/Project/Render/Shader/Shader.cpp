#include "Framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::_shaders = {};

Shader::~Shader()
{
	_blob->Release();
}

VertexShader* Shader::GetVS(wstring file)
{
	file = L"_Shader/Vertex" + file + L".hlsl";

	if (_shaders.count(file) > 0)
		return (VertexShader*)_shaders[file];

	_shaders[file] = new VertexShader(file);

	return (VertexShader*)_shaders[file];
}

PixelShader* Shader::GetPS(wstring file)
{
	file = L"_Shader/Pixel" + file + L".hlsl";

	if (_shaders.count(file) > 0)
		return (PixelShader*)_shaders[file];

	_shaders[file] = new PixelShader(file);

	return (PixelShader*)_shaders[file];
}

void Shader::Delete()
{
	for (pair<wstring, Shader*> shader : _shaders)
		delete shader.second;

	_shaders.clear();
}