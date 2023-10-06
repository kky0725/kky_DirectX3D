#include "Framework.h"
#include "ModelReader.h"

ModelReader::ModelReader(string name)
	:_name(name)
{
	ReadMaterial();
	ReadMesh();
}

ModelReader::~ModelReader()
{
	for (Material* material : _materials)
		delete material;

	for (ModelMesh* mesh : _meshes)
		delete mesh;

	_materials.clear();
	_meshes.clear();
}

void ModelReader::SetShader(wstring file)
{
	for (Material* material : _materials)
		material->SetShader(file);
}

void ModelReader::ReadMaterial()
{
	string path = "_ModelData/Material/" + _name + "/MaterialList.list";

	BinaryReader data(ToWstring(path));

	UINT size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material;

		string file = "_ModelData/Material/" + _name + "/" + data.ReadString() + ".mat";

		material->Load(ToWstring(file));

		_materials.push_back(material);
	}
}

void ModelReader::ReadMesh()
{
	string path = "_ModelData/Mesh/" + _name + ".mesh";

	BinaryReader data(ToWstring(path));

	UINT size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		ModelMesh* mesh = new ModelMesh();
		mesh->_name = data.ReadString();
		mesh->_materialIndex = data.ReadUINT();

		{
			UINT count = data.ReadUINT();

			mesh->_vertices.resize(count);

			void* ptr = mesh->_vertices.data();

			data.ReadData(&ptr, sizeof(ModelVertex) * count);
		}

		{
			UINT count = data.ReadUINT();

			mesh->_indices.resize(count);

			void* ptr = mesh->_indices.data();

			data.ReadData(&ptr, sizeof(UINT) * count);
		}

		_meshes.push_back(mesh);
	}
}
