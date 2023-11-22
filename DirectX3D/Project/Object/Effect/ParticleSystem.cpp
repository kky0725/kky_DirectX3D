#include "Framework.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(string file)
{
	Load(file);
	
	_instanceData.resize(_data.count);
	_instanceBuffer = new VertexBuffer(_instanceData);

	Init();
}

ParticleSystem::~ParticleSystem()
{
	delete _quad;
	delete _instanceBuffer;
}

void ParticleSystem::Update()
{
	if (!IsActive())
		return;

	_lifeTime += Time::Delta();

	UpdatePhysics();
	UpdateColor();

	_quad->Update();

	if (_lifeTime > _data.duration)
	{
		if (_data.isLoop)
			Init();
		else
			Stop();
	}
}

void ParticleSystem::Render()
{
	if (!IsActive())
		return;

	if (_data.isAdditive)
		STATE->AdditiveBegin();
	else
		STATE->AlphaBegin();

	_instanceBuffer->IASetBuffer(1);

	STATE->DepthWriteMaskZero();

	_quad->RenderInstanced(_drawCount);

	STATE->AlphaEnd();
	STATE->DepthEnable();
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
	_quad->IsActive() = true;

	_quad->_translation = pos;
	_quad->_rotation = rot;

	Init();
}

void ParticleSystem::Stop()
{
	_quad->IsActive() = false;
}

void ParticleSystem::UpdatePhysics()
{
	_drawCount = 0;

	for (ParticleInfo& info : _particleInfos)
	{
		if (info.startTime > _lifeTime)
			continue;

		info.velocity += info.acceleration * Time::Delta();

		info.transform._translation += info.velocity * info.speed * Time::Delta();

		info.transform._rotation.z += info.angleVelocity * Time::Delta();

		if (_data.isBillboard)
		{
			//info.transform._rotation.y = CAMERA->_rotation.y;

			//Vector3 dir = info.transform.GetGlobalPosition() - CAMERA->GetGlobalPosition();

			//float angle = atan2f(dir.x, dir.z);

			//info.transform._rotation.y = angle;

			Vector3 rot = CAMERA->_rotation;

			rot.z = info.transform._rotation.z;

			info.transform._rotation = rot;
		}

		float timeScale = (_lifeTime - info.startTime) / (_data.duration - info.startTime);

		info.transform._scale = LERP(info.startScale, info.endScale, timeScale);

		info.transform.Update();

		//_instanceData[_drawCount].color.x = Random(0.0f, 1.0f);
		//_instanceData[_drawCount].color.y = Random(0.0f, 1.0f);
		//_instanceData[_drawCount].color.z = Random(0.0f, 1.0f);
		_instanceData[_drawCount++].transform = XMMatrixTranspose(info.transform.GetWorld());
	}

	_instanceBuffer->UpdateVertex(_instanceData.data(), _drawCount);
}

void ParticleSystem::UpdateColor()
{
	float timeScale = _lifeTime / _data.duration;

	Vector4 color;
	color.x = LERP(_data.startColor.x, _data.endColor.x, timeScale);
	color.y = LERP(_data.startColor.y, _data.endColor.y, timeScale);
	color.z = LERP(_data.startColor.z, _data.endColor.z, timeScale);
	color.w = LERP(_data.startColor.w, _data.endColor.w, timeScale);

	_quad->GetMaterial()->GetBuffer()->data.diffuse = color;
}

void ParticleSystem::Init()
{
	_lifeTime = 0.0f;
	_drawCount = 0;
	_data.count = _particleCount;

	_instanceData.clear();
	_particleInfos.clear();


	_instanceData.resize(_data.count);
	_particleInfos.resize(_data.count);

	//UINT count = 0;

	for (ParticleInfo& info : _particleInfos)
	{
		info.transform._translation = Random(_data.minStartPos, _data.maxStartPos);
		info.velocity = Random(_data.minVelocity, _data.maxVelocity);
		info.acceleration = Random(_data.minAcceleration, _data.maxAcceleration);
		info.startScale = Random(_data.minStartScale, _data.maxStartScale);
		info.endScale = Random(_data.minEndScale, _data.maxEndScale);
		info.speed = Random(_data.minSpeed, _data.maxSpeed);
		info.angleVelocity = Random(_data.minAngularVelocity, _data.maxAngularVelocity);
		info.startTime = Random(_data.minStartTime, _data.maxStartTime);

		info.velocity.Normalize();

		//_instanceData[count].color.x = Random(0.0f, 1.0f);
		//_instanceData[count].color.y = Random(0.0f, 1.0f);
		//_instanceData[count].color.z = Random(0.0f, 1.0f);

		//count++;
	}
}

void ParticleSystem::Load(string file)
{
	BinaryReader* data = new BinaryReader(file);

	wstring diffusePath = data->ReadWString();

	_quad = new Quad();
	_quad->GetMaterial()->SetShader(L"18Particle");
	_quad->GetMaterial()->SetDiffuseMap(diffusePath);

	ParticleData* temp = new ParticleData();
	data->ReadData((void**)&temp, sizeof(ParticleData));

	_data = *temp;

	_particleCount = _data.count;

	delete temp;
	delete data;
}
