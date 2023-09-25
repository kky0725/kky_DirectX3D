#include "Framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor(UINT height, UINT width)
	: _height(height), _width(width)
{
	_material = new Material();

	_worldBuffer = new MatrixBuffer();

	BinaryReader data(L"HeigthMap");

	if (data.Succeeded())
	{
		wstring heightPath = data.ReadWString();

		_heightMap = Texture::Load(heightPath);
	}

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);

	_rayBuffer		= new RayBuffer();
	_computeShader	= Shader::GetCS(L"ComputePicking");

	_polygonCount = _indices.size() / 3;

	_input = new InputDesc[_polygonCount];

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i].index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0].pos;
		_input[i].v1 = _vertices[index1].pos;
		_input[i].v2 = _vertices[index2].pos;
	}

	_structuredBuffer = new StructuredBuffer(_input, sizeof(InputDesc), _polygonCount, sizeof(OutputDesc), _polygonCount);

	_output = new OutputDesc[_polygonCount];

	_brushBuffer = new BrushBuffer();
}

TerrainEditor::~TerrainEditor()
{
	if (_heightMap != nullptr)
	{
		BinaryWriter data(L"HeightMap");

		data.WriteData(_heightMap->GetPath());
	}

	delete _mesh;
	delete _worldBuffer;
	delete _material;

	delete[] _input;
	delete[] _output;

	delete _rayBuffer;
	delete _structuredBuffer;
	delete _brushBuffer;
}

void TerrainEditor::Update()
{
	Transform::Update();

	_brushBuffer->data.location = _pickedPos;

	if (Picking(&_pickedPos) && KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
		AdjustHeight();

	if (KEY_PRESS(VK_LSHIFT))
		_isRaise = false;
	else
		_isRaise = true;
}

void TerrainEditor::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	_brushBuffer->SetPSBuffer(10);

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void TerrainEditor::Debug()
{
	if (ImGui::BeginChild("TerrainEditor", ImVec2(250, 100), true))
	{
		ImGui::Text("PickedPos : %.1f, %.1f, %.1f", _pickedPos.x, _pickedPos.y, _pickedPos.z);

		if (ImGui::BeginMenu("TerrainBrush"))
		{
			ImGui::ColorEdit3("BrushColor", (float*)&_brushBuffer->data.color);
			ImGui::SliderFloat("BrushIntensity", &_adjustValue, 1.0f, 50.0f);
			ImGui::SliderFloat("BrushRange", &_brushBuffer->data.range, 1.0f, 50.0f);

			const char* typeList[] = { "Circle", "Rect" };

			ImGui::Combo("BrushType", &_brushBuffer->data.type, typeList, 2);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Save/Load HeightMap"))
		{
			SaveHeightDialog();
			LoadHeightDialog();

			ImGui::EndMenu();
		}

		_material->PostRender();
	}

	ImGui::EndChild();
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(mousePos);
	
	_rayBuffer->data.origin		= ray.origion;
	_rayBuffer->data.direction	= ray.direction;
	_rayBuffer->data.outputSize = _polygonCount;

	_rayBuffer->SetCSBuffer(0);

	/////////

	_structuredBuffer->SetSRV();
	_structuredBuffer->SetUAV();

	_computeShader->SetShader();

	UINT gruopCount = ceil(_polygonCount / 1024.0f);

	DC->Dispatch(gruopCount, 1, 1);

	_structuredBuffer->Copy(_output, sizeof(OutputDesc) * _polygonCount);

	float minDistance = FLT_MAX;

	for (UINT i = 0; i < _polygonCount; i++)
	{
		if (_output[i].isPicked)
		{
			if (minDistance > _output[i].distance)
			{ 
				minDistance = _output[i].distance;
			}
		}
	}

	if (minDistance < FLT_MAX)
	{
		*position = ray.origion + ray.direction * minDistance;

		return true;
	}

	return false;
}

void TerrainEditor::SaveHeightMap(wstring file)
{
	file = L"_Texture/" + file;

	UINT size = _width * _height * 4;

	uint8_t* pixels = new uint8_t[size];

	for (UINT i = 0; i < size / 4; i++)
	{
		float y = _vertices[i].pos.y;

		uint8_t height = y * 255.0f / MAP_HEIGHT;

		pixels[4 * i + 0] = height;
		pixels[4 * i + 1] = height;
		pixels[4 * i + 2] = height;
		pixels[4 * i + 3] = 255.0f;
	}

	Image image;

	image.width = _width;
	image.height = _height;
	image.pixels = pixels;
	image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	image.rowPitch = _width * 4;
	image.slicePitch = size;

	SaveToWICFile(image, WIC_FLAGS_FORCE_RGB, GetWICCodec(WIC_CODEC_PNG), file.c_str());
}

void TerrainEditor::LoadHeightMap(wstring file)
{
	_heightMap = Texture::Load(file);

	if (_mesh != nullptr)
		delete _mesh;

	_vertices.clear();
	_indices.clear();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);

	CreateCompute();
}

void TerrainEditor::SaveHeightDialog()
{
	if (ImGui::Button("Save HeightMap"))
	{
		Dialog->OpenDialog("SaveKey", "Save", ".png", "_Texture/HeightMap/");
	}

	if (Dialog->Display("SaveKey", 32, { 500, 400 }))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());

			SaveHeightMap(ToWstring(path));
		}

		Dialog->Close();
	}
}

void TerrainEditor::LoadHeightDialog()
{
	if (ImGui::Button("Load HeightMap"))
	{
		Dialog->OpenDialog("LoadKey", "Load", ".png", "_Texture/HeightMap/");
	}

	if (Dialog->Display("LoadKey", 32, { 500, 400 }))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());

			LoadHeightMap(ToWstring(path));
		}

		Dialog->Close();
	}
}

void TerrainEditor::CreateMesh()
{
	vector<Vector4> colors;

	if (_heightMap != nullptr)
	{
		_width = _heightMap->GetSize().x;
		_height = _heightMap->GetSize().y;

		colors = _heightMap->ReadPixels();
	}

	//Vertex
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexType vertex;
			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x = x / (_width - 1);
			vertex.uv.y = 1 - z / (_height - 1);

			if (colors.size() > 0)
			{
				UINT index = x + z * _width;
				vertex.pos.y = colors[index].x * MAP_HEIGHT;
			}

			_vertices.push_back(vertex);
		}
	}

	//Indices
	for (float z = 0; z < _height - 1; z++)
	{
		for (float x = 0; x < _width - 1; x++)
		{
			UINT LB = x + 0 + (z + 0) * _width;
			UINT RB = x + 1 + (z + 0) * _width;
			UINT LT = x + 0 + (z + 1) * _width;
			UINT RT = x + 1 + (z + 1) * _width;
			_indices.push_back(LT);
			_indices.push_back(RT);
			_indices.push_back(LB);
			_indices.push_back(LB);
			_indices.push_back(RT);
			_indices.push_back(RB);
		}
	}
}

void TerrainEditor::CreateNormal()
{
	for (VertexType& vertex : _vertices)
		vertex.normal = Vector3();

	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0].pos;
		Vector3 p1 = _vertices[index1].pos;
		Vector3 p2 = _vertices[index2].pos;

		Vector3 v01 = p1 - p0;
		Vector3 v02 = p2 - p0;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		_vertices[index0].normal += normal;
		_vertices[index1].normal += normal;
		_vertices[index2].normal += normal;
	}
}

void TerrainEditor::CreateTangent()
{
	for (VertexType& vertex : _vertices)
		vertex.tangent = Vector3();

	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0].pos;
		Vector3 p1 = _vertices[index1].pos;
		Vector3 p2 = _vertices[index2].pos;

		Vector2 uv0 = _vertices[index0].uv;
		Vector2 uv1 = _vertices[index1].uv;
		Vector2 uv2 = _vertices[index2].uv;

		Vector3 e01 = p1 - p0;
		Vector3 e02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		float D = 1.0f / (u1 * v2 - v1 * u2);

		Vector3 tangent = D * (e01 * v2 - e02 * v1);

		_vertices[index0].tangent += tangent;
		_vertices[index1].tangent += tangent;
		_vertices[index2].tangent += tangent;
	}

	for (VertexType& vertex : _vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
	}
}

void TerrainEditor::CreateCompute()
{
	_polygonCount = _indices.size() / 3;

	if (_input != nullptr)
		delete[] _input;

	_input = new InputDesc[_polygonCount];

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i].index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0].pos;
		_input[i].v1 = _vertices[index1].pos;
		_input[i].v2 = _vertices[index2].pos;
	}

	if (_structuredBuffer != nullptr)
		delete _structuredBuffer;

	_structuredBuffer = new StructuredBuffer
	(
		_input,
		sizeof(InputDesc),
		_polygonCount,
		sizeof(OutputDesc),
		_polygonCount
	);

	if (_output != nullptr)
		delete[] _output;

	_output = new OutputDesc[_polygonCount];
}

void TerrainEditor::AdjustHeight()
{
	switch (_brushBuffer->data.type)
	{
	case 0:
		for (VertexType& vertex : _vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(_pickedPos.x, 0.0f, _pickedPos.z);

			float distance = (p1 - p2).Length();

			float value = _adjustValue * max(0, cos(XM_PIDIV2 * distance / _brushBuffer->data.range));

			if (distance <= _brushBuffer->data.range)
			{
				if(_isRaise)
					vertex.pos.y += value * Time::Delta();
				else
					vertex.pos.y -= value * Time::Delta();

				if (vertex.pos.y > MAP_HEIGHT)
					vertex.pos.y = MAP_HEIGHT;

				if (vertex.pos.y < 0)
					vertex.pos.y = 0;
			}
		}
		break;
	case 1:
		for (VertexType& vertex : _vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(_pickedPos.x, 0.0f, _pickedPos.z);

			//float distanceX = abs(p1.x - p2.x);
			//float distanceZ = abs(p1.z - p2.z);

			Vector3 distance = p1 - p2;

			if (abs(distance.x) <= _brushBuffer->data.range && abs(distance.z) <= _brushBuffer->data.range)
			{
				if (_isRaise)
					vertex.pos.y += _adjustValue * Time::Delta();
				else
					vertex.pos.y -= _adjustValue * Time::Delta();
				
				if (vertex.pos.y > MAP_HEIGHT)
					vertex.pos.y = MAP_HEIGHT;

				if (vertex.pos.y < 0)
					vertex.pos.y = 0;
			}
		}
		break;
	default:
		break;
	}

	CreateNormal();
	CreateTangent();

	_mesh->UpdateVertex(_vertices.data(), _vertices.size());

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i].index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0].pos;
		_input[i].v1 = _vertices[index1].pos;
		_input[i].v2 = _vertices[index2].pos;
	}

	_structuredBuffer->UpdateInput(_input);
}
