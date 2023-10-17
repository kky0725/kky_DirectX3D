#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(string name, wstring shaderFile)
	:_name(name)
{
	_reader = new ModelReader(name);
	_reader->SetShader(shaderFile);

	_frameBuffer = new FrameBuffer();
}

ModelAnimator::~ModelAnimator()
{
	delete _reader;
	delete _frameBuffer;
}

void ModelAnimator::Update()
{
	Transform::Update();

	static float time = 0.0f;
	time += Time::Delta();

	_frameBuffer->data.curFrame = time;
}

void ModelAnimator::Render()
{
	Transform::SetWorld();

	_frameBuffer->SetVSBuffer(3);

	DC->VSSetShaderResources(0, 1, &_srv);

	_reader->Render();
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

		for (BoneData bone : _reader->_bones)
		{

		}
	}
}
