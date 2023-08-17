#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


	D3DCompileFromFile
	(
		file.c_str(),
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		flags,
		0,
		&_blob,
		nullptr
	);

	DEVICE->CreatePixelShader
	(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		&_pixelShader
	);
}

PixelShader::~PixelShader()
{
	_pixelShader->Release();
}

void PixelShader::SetShader()
{
	DC->PSSetShader(_pixelShader, nullptr, 0);
}
