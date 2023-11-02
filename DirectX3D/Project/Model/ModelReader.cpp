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

void ModelReader::Render()
{
	for (ModelMesh* mesh : _meshes)
		mesh->Render();
}

void ModelReader::RenderInstanced(UINT instanceCount)
{
	for (ModelMesh* mesh : _meshes)
		mesh->RenderInstanced(instanceCount);
}

void ModelReader::Debug()
{
	for (Material* material : _materials)
		material->Debug();

}

UINT ModelReader::GetBoneIndex(string name)
{
	if (HasBone(name))
		return _boneMap[name];

	return 0;
}

UINT ModelReader::GetNodeIndex(string name)
{
	for (NodeData node : _nodes)
	{
		if (node.name == name)
			return node.index;
	}

	return 0;
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

		UINT materialIndex = data.ReadUINT();
		mesh->_material = _materials[materialIndex];

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

		mesh->CreateMesh();

		_meshes.push_back(mesh);
	}

	size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		NodeData node;
		node.index = data.ReadInt();
		node.name = data.ReadString();
		node.parent = data.ReadInt();
		node.transform = data.ReadMatrix();

		_nodes.emplace_back(node);
	}

	size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		BoneData bone;

		bone.index = data.ReadInt();
		bone.name = data.ReadString();
		bone.offset = data.ReadMatrix();

		_bones.emplace_back(bone);

		_boneMap.emplace(bone.name, bone.index);
	}
}
