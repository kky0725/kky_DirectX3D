#include "Framework.h"
#include "Particle.h"

Particle::Particle()
{
	_material = new Material();
}

Particle::~Particle()
{
	delete _material;
	delete _vertexBuffer;
}

void Particle::Render()
{
	if (!_isActive)
		return;

	if (_isAdditive)
		STATE->AdditiveBegin();
	else
		STATE->AlphaBegin();

	STATE->DepthWriteMaskZero();

	_vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	_material->SetMaterial();
	_geometryShader->SetShader();

	DC->Draw(_drawCount, 0);

	DC->GSSetShader(nullptr, nullptr, 0);

	STATE->AlphaEnd();
	STATE->DepthEnable();
}

void Particle::Play(Vector3 position)
{
	_isActive = true;

	this->_postition = position;
}

void Particle::Stop()
{
	_isActive = false;
}

