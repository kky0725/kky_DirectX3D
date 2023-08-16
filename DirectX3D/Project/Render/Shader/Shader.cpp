#include "Framework.h"
#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	_blob->Release();
}

VertexShader* Shader::GetVS(wstring file)
{


	return nullptr;
}

PixelShader* Shader::GetPS(wstring file)
{
	return nullptr;
}

void Shader::Delete()
{
}