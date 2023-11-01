#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	//_quads.resize(COUNT * COUNT);

	//for (float x = 0; x < COUNT; x++)
	//{
	//	for (float y = 0; y < COUNT; y++)
	//	{
	//		_quads[x + y * COUNT] = new Quad();
	//		_quads[x + y * COUNT]->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	//		_quads[x + y * COUNT]->_translation = { 2 * x, 2 * y, 1 };

	//	}
	//}

	_quad = new Quad();
	_quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	_quad->GetMaterial()->SetShader(L"06TextureInstancing");

	_instanceData.resize(COUNT * COUNT);

	for (float x = 0; x < COUNT; x++)
	{
		for (float y = 0; y < COUNT; y++)
		{
			Matrix transform = XMMatrixTranslation(2 * x, 2 * y, 1);
			
			_instanceData[x + y * COUNT].Transform = XMMatrixTranspose(transform);
			_instanceData[x + y * COUNT].color = { MyMath::Random(0.0f, 1.0f), MyMath::Random(0.0f, 1.0f), MyMath::Random(0.0f, 1.0f), 1.0f};
		}
	}

	_instanceBuffer = new VertexBuffer(_instanceData);
}

InstancingScene::~InstancingScene()
{
	//for (Quad* quad : _quads)
	//	delete quad;

	//_quads.clear();

	delete _quad;
	delete _instanceBuffer;
}

void InstancingScene::Update()
{
	//for (Quad* quad : _quads)
	//	quad->Update();
}

void InstancingScene::PreRender()
{
}

void InstancingScene::Render()
{
	//for (Quad* quad : _quads)
	//	quad->Render();

	_instanceBuffer->IASetBuffer(1);

	_quad->RenderInstanced(_instanceData.size());
}

void InstancingScene::PostRender()
{
}


