#include "Framework.h"
#include "Model.h"

Model::Model(string name, wstring shaderFile)
{
	_reader = new ModelReader(name);
	//_worldBuffer = new MatrixBuffer();

	_reader->SetShader(shaderFile);
}

Model::~Model()
{
	delete _reader;
	//delete _worldBuffer;
}

void Model::Update()
{
	Transform::Update();
	//_worldBuffer->SetData(_world);
}

void Model::Render()
{
	//_worldBuffer->SetVSBuffer(0);
	Transform::SetWorld();
	_reader->Render();
}

void Model::RenderInstanced(UINT instanceCount)
{
	Transform::SetWorld();
	_reader->RenderInstanced(instanceCount);
}
