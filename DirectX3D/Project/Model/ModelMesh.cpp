#include "Framework.h"
#include "ModelMesh.h"

ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
	delete _meshes;
}
