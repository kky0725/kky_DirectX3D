#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	_terrain = new Terrain(L"LandScape/Dirt2.png", L"HeightMap/HeightMap.png");
	_terrain->Update();
	//for (UINT i = 0; i < 1000; i++)
	//{
	//	Vector2 size;

	//	size.x = Random(3.0f, 10.0f);
	//	size.y = Random(3.0f, 10.0f);

	//	Quad* tree = new Quad(size);
	//	tree->GetMaterial()->SetDiffuseMap(L"Landscape/Tree.png");
	//	
	//	tree->GetMaterial()->SetShader(L"Texture");

	//	Vector3 pos;
	//	pos.x = Random(0.0f, _terrain->GetSize().x);
	//	pos.z = Random(0.0f, _terrain->GetSize().y);

	//	pos.y = _terrain->GetHeight(pos) + size.y * 0.5f;

	//	tree->_translation = pos;

	//	_trees.emplace_back(tree);
	//}

	_material = new Material();
	_material->SetShader(L"13BillBoard");
	_material->SetDiffuseMap(L"Landscape/Tree.png");

	_geometryShader = Shader::GetGS(L"13Billboard");

	_vertices.reserve(COUNT);

	for (UINT i = 0; i < COUNT; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Vector3 pos;
		pos.x = Random(0.0f, _terrain->GetSize().x);
		pos.z = Random(0.0f, _terrain->GetSize().y);

		pos.y = _terrain->GetHeight(pos) + size.y * 0.5f;

		VertexTexture vertex;
		vertex.pos = pos;
		vertex.uv  = size;

		_vertices.emplace_back(vertex);
	}

	_vertexBuffer = new VertexBuffer(_vertices);

	//_drawVertices.resize(COUNT);
	//_vertexBuffer = new VertexBuffer(_drawVertices);
}

BillboardScene::~BillboardScene()
{
	delete _terrain;

	//for (Quad* tree : _trees)
	//	delete tree;
	//_trees.clear();

	delete _material;
	delete _vertexBuffer;
}

void BillboardScene::Update()
{
	//for (Quad* tree : _trees)
	//{
	//	//tree->_rotation = CAMERA->_rotation;//카메라 방향으로 회전

	//	Vector3 dir = tree->GetGlobalPosition() - CAMERA->GetGlobalPosition();//카메라를 바라보게 회전

	//	float angle = atan2f(dir.x, dir.z);

	//	tree->_rotation.y = angle;

	//	tree->Update();
	//}

//	_drawCount = 0;
//
//	for (UINT i = 0; i < COUNT; i++)
//	{
//		if (CAMERA->ContainPoint(_vertices[i].pos))
//		{
//			_drawVertices[_drawCount++] = _vertices[i];
//		}
//	}
//
//	_vertexBuffer->UpdateVertex(_drawVertices.data(), _drawCount);
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

	//for (Quad* tree : _trees)
	//	tree->Render();

	_vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

			_material->SetMaterial();
	  _geometryShader->SetShader();

	DC->Draw(_drawCount, 0);

	DC->GSSetShader(nullptr, nullptr, 0);

	StateManager::GetInstance()->AlphaEnd();
	//StateManager::GetInstance()->DepthEnable();

}

void BillboardScene::PostRender()
{
}


