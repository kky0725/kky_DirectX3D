#include "Framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::_shaders = {};

Shader::~Shader()
{
	_blob->Release();
}

VertexShader* Shader::GetVS(wstring file)
{
	wstring key = file;

	file = L"_Shader/Vertex" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (_shaders.count(file) > 0)
		return (VertexShader*)_shaders[file];

	_shaders[file] = new VertexShader(file);
	_shaders[file]->_path = key;

	return (VertexShader*)_shaders[file];
}

PixelShader* Shader::GetPS(wstring file)
{
	wstring key = file;

	file = L"_Shader/Pixel" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (_shaders.count(file) > 0)
		return (PixelShader*)_shaders[file];

	_shaders[file] = new PixelShader(file);
	_shaders[file]->_path = key;

	return (PixelShader*)_shaders[file];
}

ComputeShader* Shader::GetCS(wstring file)
{
	wstring key = file;

	file = L"_Shader/" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (_shaders.count(file) > 0)
		return (ComputeShader*)_shaders[file];

	_shaders[file] = new ComputeShader(file);
	_shaders[file]->_path = key;

	return (ComputeShader*)_shaders[file];
}

void Shader::Delete()
{
	for (pair<wstring, Shader*> shader : _shaders)
		delete shader.second;

	_shaders.clear();
}