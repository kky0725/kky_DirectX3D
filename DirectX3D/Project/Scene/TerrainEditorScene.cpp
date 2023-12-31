#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	_terrainEidtor = new TerrainEditor();

	//RawData();
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete _terrainEidtor;
}

void TerrainEditorScene::Update()
{
	_terrainEidtor->Update();
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{	
	//RS->ChangeState(D3D11_FILL_WIREFRAME);
	_terrainEidtor->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);
}

void TerrainEditorScene::PostRender()
{
	_terrainEidtor->Debug();
	_terrainEidtor->Getmaterial()->SaveMapDialog();
	_terrainEidtor->Getmaterial()->LoadMapDialog();

}

void TerrainEditorScene::RawData()
{
	ComputeShader* shader = Shader::GetCS(L"ByteShader");

	struct Output
	{
		UINT groupID[3];
		UINT groupThereadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT size = 10 * 8 * 3  * 2;

	Output* output = new Output[size];

	RawBuffer* buffer = new RawBuffer(nullptr, sizeof(Output) * size);

	ID3D11UnorderedAccessView* uav = buffer->GetUAV();

	shader->SetShader();

	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);

	DC->Dispatch(2, 1, 1);//comupte�� ����

	buffer->Copy(output, sizeof(Output) * size);

	FILE* file;
	fopen_s(&file, "_TextData/RawTest.csv", "w");

	for (UINT i = 0; i < size;i++)
	{
		fprintf
		(
			file,
			"%d, %d,%d,%d, %d,%d,%d, %d,%d,%d, %d,\n",
			i,
			output[i].groupID[0],
			output[i].groupID[1],
			output[i].groupID[2],
			output[i].groupThereadID[0],
			output[i].groupThereadID[1],
			output[i].groupThereadID[2],
			output[i].dispatchThreadID[0],
			output[i].dispatchThreadID[1],
			output[i].dispatchThreadID[2],
			output[i].groupIndex
		);
	}

	fclose(file);

	delete buffer;

	delete[] output;
}
