#include "Framework.h"
#include "ParticleEditorScene.h"

ParticleEditorScene::ParticleEditorScene()
{
	_quad = new Quad();

	//_quad->GetMaterial()->SetShader(L"18Particle");
	_quad->GetMaterial()->SetShader(L"06TextureInstancing");
	_quad->GetMaterial()->SetDiffuseMap(L"Effect/Snow.png");

	_instanceData.resize(MAX_COUNT);

	_instanceBuffer = new VertexBuffer(_instanceData);

	Init();
}

ParticleEditorScene::~ParticleEditorScene()
{
	delete _quad;
	delete _instanceBuffer;
}

void ParticleEditorScene::Update()
{
	_lifeTime += Time::Delta();

	UpdatePhysics();
	UpdateColor();

	_quad->Update();

	if (_lifeTime > _data.duration)
		Init();
}

void ParticleEditorScene::PreRender()
{
}

void ParticleEditorScene::Render()
{

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

void ParticleEditorScene::PostRender()
{
}

void ParticleEditorScene::UpdatePhysics()
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

		_instanceData[_drawCount++].transform = XMMatrixTranspose(info.transform.GetWorld());
	}

	_instanceBuffer->UpdateVertex(_instanceData.data(), _drawCount);
}

void ParticleEditorScene::UpdateColor()
{
	float timeScale = _lifeTime / _data.duration;

	Vector4 color;
	color.x = LERP(_data.startColor.x, _data.endColor.x, timeScale);
	color.y = LERP(_data.startColor.y, _data.endColor.y, timeScale);
	color.z = LERP(_data.startColor.z, _data.endColor.z, timeScale);
	color.w = LERP(_data.startColor.w, _data.endColor.w, timeScale);

	_quad->GetMaterial()->GetBuffer()->data.diffuse = color;
}

void ParticleEditorScene::Init()
{
	_lifeTime = 0.0f;
	_drawCount = 0;
	_data.count = _particleCount;

	 _instanceData.resize(_data.count);
	_particleInfos.resize(_data.count);

	for (ParticleInfo& info : _particleInfos)
	{
		info.transform._translation	= Random(_data.minStartPos,			_data.maxStartPos);
		info.velocity				= Random(_data.minVelocity,			_data.maxVelocity);
		info.acceleration			= Random(_data.minAcceleration,		_data.maxAcceleration);
		info.startScale				= Random(_data.minStartScale,		_data.maxStartScale);
		info.endScale				= Random(_data.minEndScale,			_data.maxEndScale);
		info.speed					= Random(_data.minSpeed,			_data.maxSpeed);
		info.angleVelocity			= Random(_data.minAngularVelocity,	_data.maxAngularVelocity);
		info.startTime				= Random(_data.minStartTime,		_data.maxStartTime);

		info.velocity.Normalize();
	}
}

void ParticleEditorScene::Save(string file)
{
}

void ParticleEditorScene::Load(string file)
{
}

void ParticleEditorScene::SaveDialog()
{
}

void ParticleEditorScene::LoadDialog()
{
}

void ParticleEditorScene::EditTexture()
{
}

