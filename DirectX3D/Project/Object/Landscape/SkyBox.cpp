#include "Framework.h"
#include "SkyBox.h"

SkyBox::SkyBox(wstring file)
{
	_sphere = new Sphere();
	_sphere->GetMaterial()->SetShader(L"05SkyBox");

	_rs = new RasterizerState();
	_rs->FrontCounterClockWise(true);

	_cubeMap = Texture::Get(file);
}

SkyBox::~SkyBox()
{
	delete _sphere;
	delete _rs;
}

void SkyBox::Render()
{
	_cubeMap->PSSetShaderResources(10);

	_rs->SetState();
	StateManager::GetInstance()->DepthDisable();

	_sphere->Render();

	RS->SetState();
	StateManager::GetInstance()->DepthEnable();
}
