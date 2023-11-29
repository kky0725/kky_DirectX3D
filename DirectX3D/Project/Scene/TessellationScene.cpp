#include "Framework.h"
#include "TessellationScene.h"

TessellationScene::TessellationScene()
{
	_material = new Material(L"23Triangle");
	
	_hullShader = Shader::GetHS(L"23Triangle");
	_domainShader = Shader::GetDS(L"23Triangle");

	_vertices =
	{
		{-0.9f, -0.9f, 0.0f},
		{+0.0f, +0.9f, 0.0f},
		{+0.9f, -0.9f, 0.0f}
	};

	_vertexBuffer = new VertexBuffer(_vertices);

	_edgeBuffer = new FloatValueBuffer();
	_insideBuffer = new FloatValueBuffer();

	_edgeBuffer->data = {1, 1, 1, 1};
	_insideBuffer->data = {1, 1, 1, 1};
}

TessellationScene::~TessellationScene()
{
	delete _material;
	delete _vertexBuffer;
	delete _edgeBuffer;
	delete _insideBuffer;
}


void TessellationScene::Update()
{
}

void TessellationScene::PreRender()
{
}

void TessellationScene::Render()
{
	_edgeBuffer->SetHSBuffer(10);
	_insideBuffer->SetHSBuffer(11);

	_material->SetMaterial();

	_hullShader->SetShader();
	_domainShader->SetShader();

	_vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	DC->Draw(_vertices.size(), 0);
}

void TessellationScene::PostRender()
{
	ImGui::Text("TessFactor Option");
	ImGui::DragFloat("Edge0", & _edgeBuffer->data.value[0]);
	ImGui::DragFloat("Edge1", & _edgeBuffer->data.value[1]);
	ImGui::DragFloat("Edge2", & _edgeBuffer->data.value[2]);
	ImGui::DragFloat("Inside", & _edgeBuffer->data.value[3]);
}

