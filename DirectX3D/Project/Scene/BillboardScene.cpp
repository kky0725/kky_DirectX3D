#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	_terrain = new Terrain(L"LandScape/Dirt2.png", L"HeightMap/HeightMap.png");

	for (UINT i = 0; i < 100; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Quad* tree = new Quad(size);
		tree->GetMaterial()->SetDiffuseMap(L"Landscape/Tree.png");
		
		tree->GetMaterial()->SetShader(L"Texture");

		Vector3 pos;
		pos.x = Random(0.0f, _terrain->GetSize().x);
		pos.z = Random(0.0f, _terrain->GetSize().y);

		pos.y = _terrain->GetHeight(pos) + size.y * 0.5f;

		tree->_translation = pos;

		_trees.emplace_back(tree);
	}
}

BillboardScene::~BillboardScene()
{
	delete _terrain;

	for (Quad* tree : _trees)
		delete tree;
	_trees.clear();
}

void BillboardScene::Update()
{
	for (Quad* tree : _trees)
	{
		//tree->_rotation = CAMERA->_rotation;//카메라 방향으로 회전

		Vector3 dir = tree->GetGlobalPosition() - CAMERA->GetGlobalPosition();//카메라를 바라보게 회전

		float angle = atan2f(dir.x, dir.z);

		tree->_rotation.y = angle;

		tree->Update();
	}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
	_terrain->Render();

	//StateManager::GetInstance()->AlphaBegin();
	StateManager::GetInstance()->AlphaToCoverageEnable();
	//StateManager::GetInstance()->DepthWriteMaskZero();

	for (Quad* tree : _trees)
		tree->Render();

	StateManager::GetInstance()->AlphaEnd();
	//StateManager::GetInstance()->DepthEnable();

}

void BillboardScene::PostRender()
{
}


