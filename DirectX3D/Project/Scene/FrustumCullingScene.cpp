#include "Framework.h"
#include "FrustumCullingScene.h"

FrustumCullingScene::FrustumCullingScene()
{
	for (UINT x = 0; x < SIZE; x++)
	{
		for (UINT y = 0; y < SIZE;y++)
		{
			for (UINT z = 0; z < SIZE; z++)
			{
				Sphere* sphere = new Sphere();

				sphere->_translation = Vector3(100 * x, 100 * y, 100 * z);
				sphere->_scale *= 20.0f;
				sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
				sphere->Update();

				_spheres.emplace_back(sphere);
			}
		}
	}
}

FrustumCullingScene::~FrustumCullingScene()
{
}

void FrustumCullingScene::Update()
{
	for (Sphere* sphere : _spheres)
	{
		if (CAMERA->ContainPoint(sphere->GetGlobalPosition()))
		{
			sphere->Update();
		}
	}
}

void FrustumCullingScene::PreRender()
{
}

void FrustumCullingScene::Render()
{
	_drawCount = 0;

	for (Sphere* sphere : _spheres)
	{
		if (CAMERA->ContainSphere(sphere->GetGlobalPosition(), sphere->Radius()))
		{
			sphere->Render();
			_drawCount++;
		}
	}
}

void FrustumCullingScene::PostRender()
{
	ImGui::Text("DrawCount : %d", _drawCount);

}


