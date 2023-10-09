#include "Framework.h"
#include "Model.h"

Model::Model(string name)
{
	_reader = new ModelReader(name);
	_worldBuffer = new MatrixBuffer();

	_reader->SetShader(L"NormalMapping");
}

Model::~Model()
{
	delete _reader;
	delete _worldBuffer;
}

void Model::Update()
{
	Transform::Update();
}

void Model::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	for (Material* material : _reader->_materials)
	{
		material->SetMaterial();
	}

	for (int i = 0; i < _reader->_meshes.size(); i++)
	{
		_reader->_meshes[i]->GetMesh()->SetMesh();
		DC->DrawIndexed(_reader->_meshes[i]->GetIndicesSize(), 0, 0);
	}
}
