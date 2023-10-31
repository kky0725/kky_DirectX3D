#include "Framework.h"
#include "Sky.h"

Sky::Sky()
{
	_sphere = new Sphere();
	//_sphere->GetMaterial()->SetShader(L"05Sky");
	_sphere->GetMaterial()->SetShader(L"05SkyBox");

	_buffer = new SkyBuffer();

	_rs = new RasterizerState();
	_rs->FrontCounterClockWise(true);
}

Sky::~Sky()
{
	delete _sphere;
	delete _buffer;
	delete _rs;
}

void Sky::Render()
{
	_buffer->SetPSBuffer(10);

	_rs->SetState();
	StateManager::GetInstance()->DepthDisable();

	_sphere->Render();

	RS->SetState();
	StateManager::GetInstance()->DepthEnable();
}

void Sky::PostRender()
{
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Sky Option");

	ImGui::ColorEdit3("Center Color", (float*)&_buffer->data.centerColor, ImGuiColorEditFlags_PickerHueBar);
	ImGui::ColorEdit3("Apex   Color", (float*)&_buffer->data.apexColor, ImGuiColorEditFlags_PickerHueWheel);

	ImGui::DragFloat("Height", &_buffer->data.height);
}