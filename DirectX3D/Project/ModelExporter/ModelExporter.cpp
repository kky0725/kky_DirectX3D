#include "Framework.h"
#include "ModelExporter.h"

ModelExporter::ModelExporter(string name)
	:_name(name)
{
	_importer = new Assimp::Importer();

	_scene = _importer->ReadFile("_ModelData/FBX/" + name + ".fbx", aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	assert(_scene != nullptr);
}

ModelExporter::~ModelExporter()
{
	delete _importer;
}

void ModelExporter::ExportModel()
{
	ExportMaterial();
	ExportMesh();
}

void ModelExporter::ExportMaterial()
{
	for (UINT i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = _scene->mMaterials[i];

		Material* material = new Material();

		material->SetLabel(srcMaterial->GetName().C_Str());

		aiColor3D color;

		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->GetBuffer()->data.diffuse = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->GetBuffer()->data.specular = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->GetBuffer()->data.ambinet = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->GetBuffer()->data.emissive = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_SHININESS, material->GetBuffer()->data.shininess);

		aiString file;

		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->SetDiffuseMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->SetSpecularMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->SetNormalMap(CreateTexture(file.C_Str()));

		string savePath = "_ModelData/Material/" + _name + "/" + material->GetLabel() + ".mat";

		CreateFolder(savePath);

		material->Save(ToWstring(savePath));

		_materialNames.push_back(material->GetLabel());

		delete material;
	}

	BinaryWriter data(L"_ModelData/Material/" + ToWstring(_name) + L"/MaterialList.list");

	data.WriteData((UINT)_materialNames.size());

	for (string name : _materialNames)
		data.WriteData(name);
}

void ModelExporter::ExportMesh()
{
	ReadNode(_scene->mRootNode, 0, -1);
	ReadMesh(_scene->mRootNode);
	WriteMesh();
}

wstring ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
		return L"";

	string fileName = GetFileName(file);

	const aiTexture* texture = _scene->GetEmbeddedTexture(file.c_str());

	string path = "_Texture/Model/" + _name + "/" + fileName;

	CreateFolder(path);

	if (PathFileExistsA(path.c_str()))
		return ToWstring(path);

	if (texture == nullptr)
		return L"";

	if (texture->mHeight < 1)
	{
		BinaryWriter data(ToWstring(path));
		data.WriteData(texture->pcData, texture->mWidth);
	}
	else
	{
		Image image;
		image.width = texture->mWidth;
		image.height = texture->mHeight;
		image.pixels = (uint8_t*)texture->pcData;
		image.rowPitch = image.width * 4;
		image.slicePitch = image.width * image.height * 4;

		SaveToWICFile(image, WIC_FLAGS_NONE, GetWICCodec(WIC_CODEC_PNG), ToWstring(path).c_str());
	}

	return ToWstring(path);
}

void ModelExporter::ReadMesh(aiNode* node)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		MeshData* mesh = new MeshData();

		mesh->name = node->mName.C_Str();

		UINT index = node->mMeshes[i];

		aiMesh* srcMesh = _scene->mMeshes[index];

		mesh->materialIndex = srcMesh->mMaterialIndex;

		UINT startVertex = mesh->vertices.size();

		vector<VertexWeight> vertexWeights;
		vertexWeights.resize(srcMesh->mNumVertices);

		ReadBone(srcMesh, vertexWeights);

		mesh->vertices.resize(srcMesh->mNumVertices);

		for (UINT j = 0; j < srcMesh->mNumVertices; j++)
		{
			ModelVertex vertex;

			memcpy(&vertex.pos, &srcMesh->mVertices[j], sizeof(Vector3));

			if(srcMesh->HasTextureCoords(0))
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][j], sizeof(Vector2));

			if(srcMesh->HasNormals())
				memcpy(&vertex.normal, &srcMesh->mNormals[j], sizeof(Vector3));

			if (srcMesh->HasTangentsAndBitangents())
				memcpy(&vertex.tangent, &srcMesh->mTangents[j], sizeof(Vector3));

			if (!vertexWeights.empty())
			{
				vertexWeights[j].Normalize();
				
				vertex.indices.x = vertexWeights[j].indices[0];
				vertex.indices.y = vertexWeights[j].indices[1];
				vertex.indices.z = vertexWeights[j].indices[2];
				vertex.indices.w = vertexWeights[j].indices[3];

				vertex.weights.x = vertexWeights[j].weights[0];
				vertex.weights.y = vertexWeights[j].weights[1];
				vertex.weights.z = vertexWeights[j].weights[2];
				vertex.weights.w = vertexWeights[j].weights[3];
			}

			mesh->vertices[j] = vertex;
		}

		for (UINT j = 0; j < srcMesh->mNumFaces; j++)
		{
			aiFace& face = srcMesh->mFaces[j];

			for (UINT k = 0; k < face.mNumIndices; k++)
			{
				mesh->indices.push_back(face.mIndices[k] + startVertex);
			}
		}
		_meshes.push_back(mesh);
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadMesh(node->mChildren[i]);
	}
}

void ModelExporter::ReadNode(aiNode* node, int index, int parent)
{
	NodeData* nodeData = new NodeData();
	nodeData->index = index;
	nodeData->parent = parent;
	nodeData->name = node->mName.C_Str();

	Matrix matrix(node->mTransformation[0]);
	matrix = XMMatrixTranspose(matrix);
	XMStoreFloat4x4(&nodeData->transform, matrix);
	
	_nodes.emplace_back(nodeData);

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadNode(node->mChildren[i], _nodes.size(), index);
	}
}

void ModelExporter::ReadBone(aiMesh* mesh, vector<VertexWeight>& vertexWeights)
{
	for (UINT i = 0; i < mesh->mNumBones; i++)
	{
		UINT boneIndex = 0;

		string name = mesh->mBones[i]->mName.C_Str();

		if (_boneMap.count(name) == 0)
		{
			boneIndex = _boneCount++;
			_boneMap.emplace(name, boneIndex);

			BoneData* boneData = new BoneData();
			boneData->index = boneIndex;
			boneData->name = name;

			Matrix matrix(mesh->mBones[i]->mOffsetMatrix[0]);
			matrix = XMMatrixTranspose(matrix);
			XMStoreFloat4x4(&boneData->offset, matrix);

			_bones.emplace_back(boneData);
		}
		else
		{
			boneIndex = _boneMap[name];
		}

		for (UINT j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			UINT   index = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;

			vertexWeights[index].Add(boneIndex, weight);
		}
	}
}

void ModelExporter::WriteMesh()
{
	string path = "_ModelData/Mesh/" + _name + ".mesh";

	CreateFolder(path);

	BinaryWriter data(ToWstring(path));

	data.WriteData((UINT)_meshes.size());

	for (MeshData* mesh : _meshes)
	{
		data.WriteData(mesh->name);
		data.WriteData(mesh->materialIndex);

		data.WriteData((UINT)mesh->vertices.size());
		data.WriteData(mesh->vertices.data(), mesh->vertices.size() * sizeof(ModelVertex));

		data.WriteData((UINT)mesh->indices.size());
		data.WriteData(mesh->indices.data(), mesh->indices.size() * sizeof(UINT));

		delete mesh;
	}

	_meshes.clear();

	data.WriteData((UINT)_nodes.size());

	for (NodeData* node : _nodes)
	{
		data.WriteData(node->index);
		data.WriteData(node->name);
		data.WriteData(node->parent);
		data.WriteData(node->transform);

		delete node;
	}

	_nodes.clear();

	data.WriteData((UINT)_bones.size());

	for (BoneData* bone : _bones)
	{
		data.WriteData(bone->index);
		data.WriteData(bone->name);
		data.WriteData(bone->offset);

		delete bone;
	}

	_bones.clear();
}

