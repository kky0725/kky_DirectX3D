#include "Framework.h"
#include "Material.h"

int Material::_ID = 0;

Material::Material()
{
	_buffer = new MaterialBuffer();

	SetShader(L"TerrainBrush");

	SetDiffuseMap(L"Landscape/fieldstone_DM.tga");
	SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	SetNormalMap(L"Landscape/fieldstone_NM.tga");


	char path[128];
	GetCurrentDirectoryA(128, path);

	_projectDir = path;
	_projectDir += "_Texture/";

	_ID++;

	_label = "Material" + to_string(_ID);
}

Material::Material(wstring file)
{
	_buffer = new MaterialBuffer();

	SetDiffuseMap(L"Landscape/fieldstone_DM.tga");
	SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	SetNormalMap(L"Landscape/fieldstone_NM.tga");

	SetShader(file);

	char path[128];
	GetCurrentDirectoryA(128, path);

	_projectDir = path;
	_projectDir += "_Texture/";

	_ID++;

	_label = "Material" + to_string(_ID);
}

Material::~Material()
{
	delete _buffer;
}

void Material::SetVertexShader(wstring file)
{
	_vertexShader = Shader::GetVS(file);
}

void Material::SetPixelShader(wstring file)
{
	_pixelShader = Shader::GetPS(file);
}

void Material::SetShader(wstring file)
{
	SetVertexShader(file);
	SetPixelShader(file);
}

void Material::SetMaterial()
{
	_vertexShader->SetShader();
	_pixelShader->SetShader();

	if (_diffuseMap)
		_diffuseMap->PSSetShaderResources(0);

	if (_specularMap)
		_specularMap->PSSetShaderResources(1);

	if (_normalMap)
		_normalMap->PSSetShaderResources(2);

	_buffer->SetPSBuffer(1);
}

void Material::SetDiffuseMap(wstring file)
{
	_diffuseMap = Texture::Get(file);
	_buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	_specularMap = Texture::Get(file);
	_buffer->data.hasSpecularMap = true;
}

void Material::SetNormalMap(wstring file)
{
	_normalMap = Texture::Get(file);
	_buffer->data.hasNormalMap = true;
}

void Material::PostRender()
{
	ImGui::InputText("Label", (char*)_label.data(), 128);

	if (ImGui::BeginMenu(_label.c_str()))
	{
		ImGui::ColorEdit4((_label + "Diffuse").c_str(), (float*)&_buffer->data.diffuse);
		ImGui::ColorEdit4((_label + "Specular").c_str(), (float*)&_buffer->data.specular);
		ImGui::ColorEdit4((_label + "Ambient").c_str(), (float*)&_buffer->data.ambinet);

		ImGui::Checkbox((_label + "HasDiffuseMap").c_str(), (bool*)&_buffer->data.hasDiffuseMap);
		ImGui::Checkbox((_label + "HasSpecularMap").c_str(), (bool*)&_buffer->data.hasSpecularMap);
		ImGui::Checkbox((_label + "HasNormalMap").c_str(), (bool*)&_buffer->data.hasNormalMap);

		ImGui::SliderFloat("Shininess", &_buffer->data.shininess, 1.0f, 50.0f);
	
		if (ImGui::Button(("Save " + _label).c_str()))
			Save(ToWstring(_label + " Data"));

		if (ImGui::Button(("Load " + _label).c_str()))
			Load(ToWstring(_label + " Data"));

		ImGui::EndMenu();
	}

	SeletMap();
}

void Material::SeletMap()
{
	if (ImGui::BeginMenu(_label.c_str()))
	{
		if (ImGui::Button("DiffuseMap"))
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png,.jpg,.dds,.tga", "_Texture/");

		if (ImGui::Button("NormalMap"))
			Dialog->OpenDialog("Normal", "Select Normal", ".png,.jpg,.dds,.tga", "_Texture/");

		if (ImGui::Button("SpecularMap"))
			Dialog->OpenDialog("Specular", "Select Specular", ".png,.jpg,.dds,.tga", "_Texture/");

		if (Dialog->Display("Diffuse") || Dialog->Display("Normal") || Dialog->Display("Specular"))
		{
			if (Dialog->IsOk())
			{
				string path = Dialog->GetFilePathName();

				path = path.substr(_projectDir.size() + 1, path.size());

				wstring file = ToWstring(path);

				if(Dialog->GetOpenedKey() == "Diffuse")
					SetDiffuseMap(file);
				else if (Dialog->GetOpenedKey() == "Normal")
					SetNormalMap(file);
				else if (Dialog->GetOpenedKey() == "Specular")
					SetSpecularMap(file);
			}

			Dialog->Close();
		}
		ImGui::EndMenu();
	}
}

void Material::Save(wstring file)
{
	BinaryWriter data(file);

	data.WriteData(_label);

	if (_vertexShader)
		data.WriteData(_vertexShader->GetPath());

	if (_pixelShader)
		data.WriteData(_pixelShader->GetPath());
	else
		data.WriteData(L"");

	if (_diffuseMap)
		data.WriteData(_diffuseMap->GetPath());
	else
		data.WriteData(L"");

	if (_specularMap)
		data.WriteData(_specularMap->GetPath());
	else
		data.WriteData(L"");


	if (_normalMap)
		data.WriteData(_normalMap->GetPath());
	else
		data.WriteData(L"");
}

void Material::Load(wstring file)
{
	BinaryReader data(file);

	if (!data.Succeeded())
		return;

	_label = data.ReadString();

	wstring str;

	str = data.ReadWString();
	if (str != L"")
		_vertexShader = Shader::GetVS(str);

	str = data.ReadWString();
	if (str != L"")
		_pixelShader = Shader::GetPS(str);

	str = data.ReadWString();
	if (str != L"")
		_diffuseMap = Texture::Get(str);

	str = data.ReadWString();
	if (str != L"")
		_specularMap = Texture::Get(str);

	str = data.ReadWString();
	if (str != L"")
		_normalMap = Texture::Get(str);


}

void Material::SaveMap(wstring file)
{
	BinaryWriter data(file);

	data.WriteData(_diffuseMap->GetPath());
	data.WriteData(_specularMap->GetPath());
	data.WriteData(_normalMap->GetPath());


}

void Material::LoadMap(wstring file)
{
	BinaryReader data(file);

	SetDiffuseMap(data.ReadWString());
	SetSpecularMap(data.ReadWString());
	SetNormalMap(data.ReadWString());
}

void Material::SaveMapDialog()
{
	if (ImGui::Button("SaveMap"))
		Dialog->OpenDialog("SaveMap", "Select Map", ".materialmap", "_TextData/");

	if (Dialog->Display("SaveMap"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();
			path = path.substr(_projectDir.size() + 1, path.size());

			wstring file = ToWstring(path);
			if (Dialog->GetOpenedKey() == "SaveMap")
				SaveMap(file);
		}
		Dialog->Close();
	}
}

void Material::LoadMapDialog()
{
	if (ImGui::Button("LoadMap"))
		Dialog->OpenDialog("LoadMap", "Select Map", ".materialmap", "_TextData/");

	if (Dialog->Display("LoadMap"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();
			path = path.substr(_projectDir.size() + 1, path.size());

			wstring file = ToWstring(path);
			if (Dialog->GetOpenedKey() == "LoadMap")
				LoadMap(file);
		}
		Dialog->Close();
	}
}


