#include "Framework.h"
#include "ParticleEditorScene.h"

ParticleEditorScene::ParticleEditorScene()
{
	_quad = new Quad();

	//_quad->GetMaterial()->SetShader(L"06TextureInstancing");
	_quad->GetMaterial()->SetShader(L"18Particle");
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
	EditTexture();

	ImGui::Checkbox("isLoop",		&_data.isLoop);
	ImGui::Checkbox("idAdditive",	&_data.isAdditive);
	ImGui::Checkbox("isBillboard",	&_data.isBillboard);
	ImGui::SliderInt("ParticleCount",		 (int*) &_particleCount				,1,MAX_COUNT);
	ImGui::SliderFloat ("duration",			 (float*)& _data.duration			,0.0f,10.0f);
	ImGui::SliderFloat3("minStartPos",		 (float*)&_data.minStartPos			,-10,10);
	ImGui::SliderFloat3("maxStartPos",		 (float*)&_data.maxStartPos			,-10,10);
	ImGui::SliderFloat3("maxVelocity",		 (float*)&_data.maxVelocity			,-1,1);
	ImGui::SliderFloat3("minVelocity",		 (float*)&_data.minVelocity			,-1,1);
	ImGui::SliderFloat3("minAcceleration",	 (float*)&_data.minAcceleration		,-5,5);
	ImGui::SliderFloat3("maxAcceleration",	 (float*)&_data.maxAcceleration		,-5,5);
	ImGui::SliderFloat3("minStartScale",	 (float*)&_data.minStartScale		,0,5);
	ImGui::SliderFloat3("maxStartScale",	 (float*)&_data.maxStartScale		,0,5);
	ImGui::SliderFloat ("minEndScale",		 (float*)&_data.minEndScale			,0,5);
	ImGui::SliderFloat ("maxEndScale",		 (float*)&_data.maxEndScale			,0,5);
	ImGui::SliderFloat ("minSpeed",			 (float*)&_data.minSpeed			,0,_data.maxSpeed);
	ImGui::SliderFloat ("maxSpeed",			 (float*)&_data.maxSpeed			,_data.minSpeed, 200);
	ImGui::SliderFloat ("minAngularVelocity",(float*)&_data.minAngularVelocity	,-10,10);
	ImGui::SliderFloat ("maxAngularVelocity",(float*)&_data.maxAngularVelocity	,-10,10);
	ImGui::SliderFloat ("minStartTime",		 (float*)&_data.minStartTime		,0,_data.maxStartTime);
	ImGui::SliderFloat ("maxStartTime",		 (float*)&_data.maxStartTime		,_data.minStartTime, _data.duration);
	ImGui::ColorEdit4 ("startColor",		 (float*)&_data.startColor);
	ImGui::ColorEdit4 ("endColor",			 (float*)&_data.endColor);

	SaveDialog();
	ImGui::SameLine();
	LoadDialog();
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

		//_instanceData[_drawCount].color.x = Random(0.0f, 1.0f);
		//_instanceData[_drawCount].color.y = Random(0.0f, 1.0f);
		//_instanceData[_drawCount].color.z = Random(0.0f, 1.0f);
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

	 _instanceData.clear();
	_particleInfos.clear();


	 _instanceData.resize(_data.count);
	_particleInfos.resize(_data.count);

	//UINT count = 0;

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

		//_instanceData[count].color.x = Random(0.0f, 1.0f);
		//_instanceData[count].color.y = Random(0.0f, 1.0f);
		//_instanceData[count].color.z = Random(0.0f, 1.0f);

		//count++;
	}
}

void ParticleEditorScene::Save(string file)
{
	BinaryWriter* data = new BinaryWriter(file);

	data->WriteData(_quad->GetMaterial()->GetDiffuseMap()->GetPath());

	data->WriteData(&_data, sizeof(ParticleData));

	delete data;
}

void ParticleEditorScene::Load(string file)
{
	BinaryReader* data = new BinaryReader(file);

	wstring diffusePath = data->ReadWString();

	_quad->GetMaterial()->SetDiffuseMap(diffusePath);

	ParticleData* temp = new ParticleData();
	data->ReadData((void**) &temp, sizeof(ParticleData));

	_data = *temp;

	_particleCount = _data.count;

	delete temp;
	delete data;
}

void ParticleEditorScene::SaveDialog()
{
	if (ImGui::Button("Save"))
		Dialog->OpenDialog("Save Particle", "Save", ".fx", "_TextData/");

	if (Dialog->Display("Save Particle"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();
			path = path.substr(GetProjectDir().size(), path.size());

			if (Dialog->GetOpenedKey() == "Save Particle")
				Save(path);
		}
		Dialog->Close();
	}
}

void ParticleEditorScene::LoadDialog()
{
	if (ImGui::Button("Load"))
		Dialog->OpenDialog("Load Particle", "Load", ".fx", "_TextData/");

	if (Dialog->Display("Load Particle"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();
			path = path.substr(GetProjectDir().size(), path.size());

			if (Dialog->GetOpenedKey() == "Load Particle")
				Load(path);
		}
		Dialog->Close();
	}
}

void ParticleEditorScene::EditTexture()
{
	ImTextureID textureID = _quad->GetMaterial()->GetDiffuseMap()->GetSRV();

	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
	{
		Dialog->OpenDialog("Select Texutre", "Select Texture", ".png,.jpg,.tga", "_Texture/");
	}

	if (Dialog->Display("Select Texutre"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();
			path = path.substr(GetProjectDir().size(), path.size());

			if (Dialog->GetOpenedKey() == "Select Texutre")
				_quad->GetMaterial()->SetDiffuseMap(ToWstring(path));
		}
		Dialog->Close();
	}
}

