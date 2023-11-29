#include "Framework.h"
#include "HullShader.h"

HullShader::HullShader(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


	D3DCompileFromFile
	(
		file.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"hs_5_0",
		flags,
		0,
		&_blob,
		nullptr
	);

	DEVICE->CreateHullShader
	(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

HullShader::~HullShader()
{
	_shader->Release();
}

void HullShader::SetShader()
{
	DC->HSSetShader(_shader, nullptr, 0);
}
