#include "Framework.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(wstring frontImage, wstring backImage)
	:Quad(frontImage)
{
	_backImage = Texture::Get(backImage);

	_material->SetShader(L"04ProgressBar");

	_buffer = new FloatValueBuffer();
	_buffer->data.value[0] = 1.0f;
}

ProgressBar::~ProgressBar()
{
	delete _buffer;
}

void ProgressBar::Render()
{
	_buffer->SetPSBuffer(10);
	_backImage->PSSetShaderResources(10);

	Quad::Render();
}

void ProgressBar::SetValue(float value)
{
	_buffer->data.value[0] = value;
}

