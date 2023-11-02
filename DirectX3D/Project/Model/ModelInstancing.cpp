#include "Framework.h"
#include "ModelInstancing.h"

ModelInstancing::ModelInstancing(string name)
	:Model(name), _name(name)
{
	_instanceDatas.resize(MAX_INSTANCE);

	_instanceBuffer = new VertexBuffer(_instanceDatas);

	_reader->SetShader(L"07ModelInstancing");
}

ModelInstancing::~ModelInstancing()
{
	delete _instanceBuffer;

	for (Transform* transform : _transfroms)
		delete transform;

	_transfroms.clear();
}

void ModelInstancing::Update()
{
	_drawCount = 0;

	for (UINT i = 0; i < _transfroms.size(); i++)
	{
		if (!_transfroms[i]->IsActive())
			continue;

		_transfroms[i]->UpdateWorld();

		_instanceDatas[_drawCount].world = XMMatrixTranspose(_transfroms[i]->GetWorld());
		_instanceDatas[_drawCount].index = i;

		_drawCount++;
	}

	_instanceBuffer->UpdateVertex(_instanceDatas.data(), _drawCount);
}

void ModelInstancing::Render()
{
	_instanceBuffer->IASetBuffer(1);

	Model::RenderInstanced(_drawCount);
}

void ModelInstancing::Debug()
{
	ImGui::Text("DrawCout : %d", _drawCount);

	for (Transform* transform : _transfroms)
		transform->Debug();
}

Transform* ModelInstancing::Add()
{
	Transform* transform = new Transform();

	transform->SetLabel(_name + "_" + to_string(_transfroms.size()));
	_transfroms.emplace_back(transform);

	return transform;
}


