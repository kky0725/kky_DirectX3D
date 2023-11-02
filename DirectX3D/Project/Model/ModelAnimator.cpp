#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(string name, wstring shaderFile)
	:_name(name)
{
	_reader = new ModelReader(name);
	_reader->SetShader(shaderFile);

	_frameBuffer = new FrameBuffer();

	_ID = name;
}

ModelAnimator::~ModelAnimator()
{
	delete _reader;
	delete _frameBuffer;
}

void ModelAnimator::Update()
{
	Transform::Update();

	if (!_isPlay)
		return;
	
	UpdateFrame();
}

void ModelAnimator::Render()
{
	Transform::SetWorld();

	_frameBuffer->SetVSBuffer(3);

	DC->VSSetShaderResources(0, 1, &_srv);

	_reader->Render();
}

void ModelAnimator::RenderInstanced(UINT instanceCount)
{
	Transform::SetWorld();

	_frameBuffer->SetVSBuffer(3);

	DC->VSSetShaderResources(0, 1, &_srv);

	_reader->RenderInstanced(instanceCount);
}

void ModelAnimator::ReadClip(string file, UINT clipIndex)
{
	string path = "_ModelData/Clip/" + _name + "/" + file + to_string(clipIndex) + ".clip";

	BinaryReader data(path);

	ModelClip* clip = new ModelClip();
	clip->name			= data.ReadString();
	clip->tickPerSecond = data.ReadFloat();
	clip->frameCount	= data.ReadInt();
	clip->duration		= data.ReadFloat();

	UINT keyFrameCount = data.ReadUINT();

	for (UINT i = 0; i < keyFrameCount; i++)
	{
		KeyFrame* keyFrame = new KeyFrame();
		keyFrame->boneName = data.ReadString();

		UINT keyTransformCount = data.ReadUINT();

		if (keyTransformCount > 0)
		{
			keyFrame->transforms.resize(keyTransformCount);

			void* ptr = (void*)keyFrame->transforms.data();
			data.ReadData(&ptr, sizeof(KeyTransform) * keyTransformCount);
		}

		clip->_keyFrames.emplace(keyFrame->boneName, keyFrame);
	}

	_clips.emplace_back(clip);
}

void ModelAnimator::PlayClip(UINT clipIndex, float speed, float takeTime)
{
	_frameBuffer->data.next.clip   = clipIndex;
	_frameBuffer->data.next.speed  = speed;
	_frameBuffer->data.takeTime    = takeTime;
	_frameBuffer->data.runningTime = 0.0f;
}

void ModelAnimator::CreateTexture()
{
	UINT clipCount = _clips.size();

	_clipTransform = new ClipTransform[clipCount];
	_nodeTransform = new ClipTransform[clipCount];

	for (UINT i = 0; i < clipCount; i++)
	{
		CreateClipTransform(i);
	}

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width			  = MAX_BONE * 4;
	desc.Height			  = MAX_FRAME_KEY;
	desc.ArraySize		  = clipCount;
	desc.Format			  = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage			  = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags		  = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels		  = 1;
	desc.SampleDesc.Count = 1;

	UINT pageSize = MAX_BONE * sizeof(Matrix) * MAX_FRAME_KEY;

	void* ptr = VirtualAlloc(nullptr, pageSize * clipCount, MEM_RESERVE, PAGE_READWRITE);

	for (UINT c = 0; c < clipCount; c++)
	{
		UINT start = c * pageSize;

		for (UINT i = 0; i < MAX_FRAME_KEY; i++)
		{
			void* temp = (BYTE*)ptr + MAX_BONE * i * sizeof(Matrix) + start;

			VirtualAlloc(temp, MAX_BONE * sizeof(Matrix), MEM_COMMIT, PAGE_READWRITE);
			memcpy(temp, _clipTransform[c].transform[i], MAX_BONE * sizeof(Matrix));
		}
	}

	D3D11_SUBRESOURCE_DATA* subResources = new D3D11_SUBRESOURCE_DATA[clipCount];

	for (UINT c = 0; c < clipCount; c++)
	{
		void* temp = (BYTE*)ptr + c * pageSize;

		subResources[c].pSysMem = temp;
		subResources[c].SysMemPitch = MAX_BONE * sizeof(Matrix);
		subResources[c].SysMemSlicePitch = pageSize;
	}

	DEVICE->CreateTexture2D(&desc, subResources, &_texture);

	delete[] subResources;
	VirtualFree(ptr, 0, MEM_RELEASE); // 0?

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format					 = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension			 = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = clipCount;

	DEVICE->CreateShaderResourceView(_texture, &srvDesc, &_srv);
}

void ModelAnimator::UpdateFrame()
{
	FrameBuffer::Data& frameData = _frameBuffer->data;

	ModelClip* clip = _clips[frameData.cur.clip];

	frameData.cur.time += Time::Delta() * clip->tickPerSecond * frameData.cur.speed;

	if (frameData.cur.time >= 1.0f)
	{
		++frameData.cur.curFrame %= (clip->frameCount - 1);
		frameData.cur.time = 0.0f;

		float animRatio = (float)frameData.cur.curFrame / _clips[frameData.cur.clip]->frameCount;

		if (clip->_EndEvent != nullptr && animRatio > clip->_ratio)
			clip->_EndEvent();
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

void ModelAnimator::Debug()
{
	_reader->Debug();

	ImGui::Checkbox("IsPlay", &_isPlay);
}

Matrix ModelAnimator::GetTransformByBone(UINT boneIndex)
{
	FrameBuffer::Frame& curClip = _frameBuffer->data.cur;

	Matrix cur = _clipTransform[curClip.clip].transform[curClip.curFrame][boneIndex];

	return cur;
}

Matrix ModelAnimator::GetTransformByNode(UINT nodeIndex)
{
	FrameBuffer::Frame& curClip = _frameBuffer->data.cur;

	Matrix cur = _nodeTransform[curClip.clip].transform[curClip.curFrame + 0][nodeIndex];
	Matrix next = _nodeTransform[curClip.clip].transform[curClip.curFrame + 1][nodeIndex];

	Matrix curAnim = LERP(cur, next, curClip.time);


	FrameBuffer::Frame& nextClip = _frameBuffer->data.next;

	if (nextClip.clip == -1)
		return curAnim;

	cur = _nodeTransform[nextClip.clip].transform[nextClip.curFrame + 0][nodeIndex];
	next = _nodeTransform[nextClip.clip].transform[nextClip.curFrame + 1][nodeIndex];

	Matrix nextAnim = LERP(cur, next, nextClip.time);

	return LERP(curAnim, nextAnim, _frameBuffer->data.tweenTime);
}

void ModelAnimator::CreateClipTransform(UINT index)
{
	ModelClip* clip = _clips[index];

	for (UINT f = 0; f < clip->frameCount; f++)
	{
		UINT nodeIndex = 0;

		for (NodeData node : _reader->_nodes)
		{
			Matrix animWorld;

			KeyFrame* frame = clip->GetKeyFrames(node.name);

			if (frame != nullptr)
			{
				KeyTransform transform = frame->transforms[f];

				Matrix S = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
				Matrix R = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.rotation));
				Matrix T = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);

				animWorld = S * R * T;
			}
			else
			{
				animWorld = XMMatrixIdentity();
			}

			Matrix parentWorld;

			int parentIndex = node.parent;

			if (parentIndex < 0)
				parentWorld = XMMatrixIdentity();
			else
				parentWorld = _nodeTransform[index].transform[f][parentIndex];

			_nodeTransform[index].transform[f][nodeIndex] = animWorld * parentWorld;

			vector<BoneData> bones = _reader->_bones;

			if (_reader->HasBone(node.name))
			{
				UINT boneIndex = _reader->_boneMap[node.name];

				Matrix transform = bones[boneIndex].offset;
				transform *= _nodeTransform[index].transform[f][nodeIndex];

				_clipTransform[index].transform[f][boneIndex] = transform;
			}

			nodeIndex++;
		}
	}
}
