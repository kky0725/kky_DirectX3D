#include "Framework.h"
#include "ModelMesh.h"

ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
	delete _mesh;
	//delete _material;
}

void ModelMesh::CreateMesh()
{
	_mesh = new Mesh(_vertices, _indices);
}

void ModelMesh::Render()
{
	_material->SetMaterial();
		_mesh->SetMesh();

	DC->DrawIndexed(_indices.size(), 0, 0);
}