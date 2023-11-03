#include "Framework.h"
#include "Model.h"

Model::Model(string name, wstring shaderFile)
{
	_reader = new ModelReader(name);

	_reader->SetShader(shaderFile);
}

Model::~Model()
{
	delete _reader;
}

void Model::Update()
{
	Transform::Update();
}

void Model::Render()
{
	Transform::SetWorld();
	_reader->Render();
}

void Model::RenderInstanced(UINT instanceCount)
{
	Transform::SetWorld();
	_reader->RenderInstanced(instanceCount);
}
