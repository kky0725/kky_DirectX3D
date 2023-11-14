#include "Framework.h"
#include "ModelAnimatorInstancing.h"

ModelAnimatorInstancing::ModelAnimatorInstancing(string name)
	:ModelAnimator(name), _name(name)
{
	_instanceDatas.resize(MAX_INSTANCE);

	_instanceBuffer = new VertexBuffer(_instanceDatas);

	_reader->SetShader(L"08ModelAnimatorInstancing");

	_frameInstancingBuffer = new FrameInstancingBuffer();
}

ModelAnimatorInstancing::~ModelAnimatorInstancing()
{
	delete _instanceBuffer;
	delete _frameInstancingBuffer;

	for (Transform* transform : _transfroms)
		delete transform;

	_transfroms.clear();
}

void ModelAnimatorInstancing::Update()
{
	UpdateTransforms();
}

void ModelAnimatorInstancing::Render()
{
	if (!_texture)
		CreateTexture();

	_instanceBuffer->IASetBuffer(1);
	_frameInstancingBuffer->SetVSBuffer(4);

	ModelAnimator::RenderInstanced(_drawCount);
}

void ModelAnimatorInstancing::Debug()
{
	ImGui::Text("DrawCout : %d", _drawCount);

	for (Transform* transform : _transfroms)
		transform->Debug();
}

Transform* ModelAnimatorInstancing::Add()
{
	Transform* transform = new Transform();

	transform->SetLabel(_name + "_" + to_string(_transfroms.size()));
	_transfroms.emplace_back(transform);

	return transform;
}

void ModelAnimatorInstancing::PlayClip(UINT instanceIndex, int clip, float speed, float takeTime)
{
	_frameInstancingBuffer->data.motion[instanceIndex].next.clip = clip;
	_frameInstancingBuffer->data.motion[instanceIndex].next.speed = speed;
	_frameInstancingBuffer->data.motion[instanceIndex].takeTime = takeTime;
	_frameInstancingBuffer->data.motion[instanceIndex].runningTime = 0.0f;

	//_clips[clip]->Init();
}

Matrix ModelAnimatorInstancing::GetTransformByNode(UINT instanceIndex, int nodeIndex)
{
	FrameInstancingBuffer::Frame& curClip = _frameInstancingBuffer->data.motion[instanceIndex].cur;

	Matrix cur = _nodeTransform[curClip.clip].transform[curClip.curFrame + 0][nodeIndex];
	Matrix next = _nodeTransform[curClip.clip].transform[curClip.curFrame + 1][nodeIndex];

	Matrix curAnim = LERP(cur, next, curClip.time);


	FrameInstancingBuffer::Frame& nextClip = _frameInstancingBuffer->data.motion[instanceIndex].next;

	if (nextClip.clip == -1)
		return curAnim;

	cur = _nodeTransform[nextClip.clip].transform[nextClip.curFrame + 0][nodeIndex];
	next = _nodeTransform[nextClip.clip].transform[nextClip.curFrame + 1][nodeIndex];

	Matrix nextAnim = LERP(cur, next, nextClip.time);

	return LERP(curAnim, nextAnim, _frameInstancingBuffer->data.motion[instanceIndex].tweenTime);
}

void ModelAnimatorInstancing::UpdateFrame(UINT instanceIndex)
{
	FrameInstancingBuffer::Motion& frameData = _frameInstancingBuffer->data.motion[instanceIndex];

	ModelClip* clip = _clips[frameData.cur.clip];

	frameData.cur.time += Time::Delta() * clip->tickPerSecond * frameData.cur.speed;

	if (frameData.cur.time >= 1.0f)
	{
		++frameData.cur.curFrame %= (clip->frameCount - 1);
		frameData.cur.time = 0.0f;

		if (frameData.cur.curFrame == 0)
			clip->Init();

		float animRatio = (float)frameData.cur.curFrame / _clips[frameData.cur.clip]->frameCount;

		clip->Execute(animRatio);

		/*if (clip->_EndEvent != nullptr && animRatio > clip->_ratio)
			clip->_EndEvent();*/
	}


	//NextClip
	if (frameData.next.clip < 0)
		return;

	frameData.tweenTime += Time::Delta() / frameData.takeTime;

	clip = _clips[frameData.next.clip];

	if (frameData.tweenTime >= 1.0f)
	{
		frameData.cur = frameData.next;
		frameData.tweenTime = 0.0f;

		frameData.next.clip = -1;
		frameData.next.curFrame = 0;
		frameData.next.time = 0.0f;
	}
	else
	{
		frameData.next.time += Time::Delta() * clip->tickPerSecond * frameData.next.speed;

		if (frameData.next.time >= 1.0f)
		{
			++frameData.next.curFrame %= (clip->frameCount - 1);
			frameData.next.time = 0.0f;
		}
	}
}

void ModelAnimatorInstancing::UpdateTransforms()
{
	_drawCount = 0;

	for (UINT i = 0; i < _transfroms.size(); i++)
	{
		if (!_transfroms[i]->IsActive())
			continue;

		UpdateFrame(i);

		_transfroms[i]->UpdateWorld();

		_instanceDatas[_drawCount].world = XMMatrixTranspose(_transfroms[i]->GetWorld());
		_instanceDatas[_drawCount].index = i;

		_drawCount++;
	}

	_instanceBuffer->UpdateVertex(_instanceDatas.data(), _drawCount);
}


