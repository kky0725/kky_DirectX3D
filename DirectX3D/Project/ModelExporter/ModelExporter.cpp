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
		//material->SetDiffuseMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		//material->SetSpecularMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		//material->SetNormalMap(CreateTexture(file.C_Str()));

		string savePath = "_ModelData/Material/" + _name + ".mat";

		CreateFolder(savePath);

		material->Save(ToWstring(savePath));

		delete material;
	}
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

