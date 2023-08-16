#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	file = L"_Shader/" + file + L".hlsl";

	D3DCompileFromFile
	(
		file.c_str(),
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		flags,
		0,
		&_blob,
		nullptr
	);

	DEVICE->CreateVertexShader
	(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		&_vertexShader
	);

	CreateInputLayOut();
}

VertexShader::~VertexShader()
{
	_vertexShader->Release();
	 _inputLayout->Release();
}

void VertexShader::SetShader()
{

	DC->IASetInputLayout(_inputLayout);
	DC->VSSetShader(_vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayOut()
{
	D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};

	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;


	layoutDesc[1].SemanticName = "COLOR";
	layoutDesc[1].SemanticIndex = 0;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].AlignedByteOffset = 12;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].InstanceDataStepRate = 0;


	DEVICE->CreateInputLayout
	(
		layoutDesc,
		ARRAYSIZE(layoutDesc),
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		&_inputLayout
	);
}

