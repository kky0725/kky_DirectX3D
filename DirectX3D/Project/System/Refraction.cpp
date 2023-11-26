#include "Framework.h"
#include "Refraction.h"

UINT Refraction::_index = 0;

Refraction::Refraction(wstring file)
{
	_buffer = new WaterBuffer();

	_normalMap = Texture::Get(file);

	_renderTarget = new RenderTarget(1280, 720);
	_depthStencil = new DepthStencil(1280, 720);

	// Debug()

	_quad = new Quad(Vector2(200, 200));
	_quad->_translation = { 100, 100, 0 };

	Texture* texture = Texture::Get(L"Refraction" + to_wstring(_index++), _renderTarget->GetSRV());

	_quad->GetMaterial()->SetDiffuseMap(texture);
	_quad->UpdateWorld();
}

Refraction::~Refraction()
{
	delete _buffer;
	delete _renderTarget;
	delete _depthStencil;
	delete _quad;
}

void Refraction::Update()
{
	_buffer->data.waveTime += Time::Delta();
}

void Refraction::SetPreRender()
{
	_renderTarget->Set(_depthStencil);
}

void Refraction::SetRender()
{
	_buffer->SetPSBuffer(10);

			DC->PSSetShaderResources(11, 1, &_renderTarget->GetSRV());
	_normalMap->PSSetShaderResources(12);
}

void Refraction::PostRender()
{
	_quad->Render();
}

void Refraction::DeBug()
{
	ImGui::Text("Water Option");
	ImGui::ColorEdit4("WaveColor", (float*)&_buffer->data.color);

	ImGui::SliderFloat("WaveSpeed"		, (float*)&_buffer->data.waveSpeed	 , 0.0f,  1.0f);
	ImGui::SliderFloat("WaveScale"		, (float*)&_buffer->data.waveScale	 , 0.0f,  1.0f);
	ImGui::SliderFloat("WaveShininess"	, (float*)&_buffer->data.waveShinines, 1.0f, 50.0f);
	ImGui::SliderFloat("WaveFresnel"	, (float*)&_buffer->data.fresnel	 , 0.0f,  1.0f);
}
