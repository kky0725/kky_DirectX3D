#include "Framework.h"
#include "Material.h"

string Material::_ID = "";

Material::Material()
{
	_buffer = new MaterialBuffer();

	char path[128];
	GetCurrentDirectoryA(128, path);

	_projectDir = path;
	_projectDir += "_Texture/";

	_ID += ".";
}

Material::Material(wstring file)
{
	SetShader(file);
	_buffer = new MaterialBuffer();

	char path[128];
	GetCurrentDirectoryA(128, path);

	_projectDir = path;
	_projectDir += "_Texture/";

	_ID += ".";
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
	ImGui::ColorEdit4("Diffuse", (float*)&_buffer->data.diffuse);
	ImGui::ColorEdit4("Specular", (float*)&_buffer->data.specular);
	ImGui::ColorEdit4("Ambient", (float*)&_buffer->data.ambinet);

	ImGui::Checkbox("HasDiffuseMap", (bool*)&_buffer->data.hasDiffuseMap);
	ImGui::Checkbox("HasSpecularMap", (bool*)&_buffer->data.hasSpecularMap);
	ImGui::Checkbox("HasNormalMap", (bool*)&_buffer->data.hasNormalMap);

	ImGui::SliderFloat("Shininess", &_buffer->data.shininess, 1.0f, 50.0f);
}

void Material::SeletMap()
{
#define Dialog ImGuiFileDialog::Instance()

	if (ImGui::BeginChild(_ID.c_str(), ImVec2(100, 85), true))
	{
		if (ImGui::Button("DiffuseMap"))
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png,.jpg,.dds,.tga", "_Texture/");

		if (ImGui::Button("SpecularMap"))
			Dialog->OpenDialog("Specular", "Select Specular", ".png,.jpg,.dds,.tga", "_Texture/");

		if (ImGui::Button("NormalMap"))
			Dialog->OpenDialog("Normal", "Select Normal", ".png,.jpg,.dds,.tga", "_Texture/");

		if (Dialog->Display("Diffuse") || Dialog->Display("Specular") || Dialog->Display("Normal"))
		{
			if (Dialog->IsOk())
			{
				string path = Dialog->GetFilePathName();

				path = path.substr(_projectDir.size() + 1, path.size());

				wstring file = ToWstring(path);

				if(Dialog->GetOpenedKey() == "Diffuse")
					SetDiffuseMap(file);
				else if (Dialog->GetOpenedKey() == "Specular")
					SetSpecularMap(file);
				else if (Dialog->GetOpenedKey() == "Normal")
					SetNormalMap(file);
			}

			Dialog->Close();
		}


		ImGui::EndChild();
	}
}


