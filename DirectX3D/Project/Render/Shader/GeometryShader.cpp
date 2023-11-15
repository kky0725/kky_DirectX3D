#include "Framework.h"
#include "GeometryShader.h"

GeometryShader::GeometryShader(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


	D3DCompileFromFile
	(
		file.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"gs_5_0",
		flags,
		0,
		&_blob,
		nullptr
	);

	DEVICE->CreateGeometryShader
	(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

GeometryShader::~GeometryShader()
{
	_shader->Release();
}

void GeometryShader::SetShader()
{
	DC->GSSetShader(_shader, nullptr, 0);
}


