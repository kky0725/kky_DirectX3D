#include "Framework.h"
#include "Water.h"

Water::Water(wstring normalFile, float width, float height)
	:_size(width, height)
{
	_ID = "Water_" + to_string(_index);


	_reflection = new Reflection(this);
	_refraction = new Refraction(normalFile);

	CreateMesh();

	_mesh = new Mesh(_vertices, _indices);
	_material = new Material();
	_material->SetShader(L"21Water");
}

Water::~Water()
{
	delete _reflection;
	delete _refraction;
	delete _mesh;
	delete _material;
}

void Water::Update()
{
	Transform::Update();

	_reflection->Update();
	_refraction->Update();
}

void Water::Render()
{
	Transform::SetWorld();

		_mesh->SetMesh();
	_material->SetMaterial();

	_reflection->SetRender();
	_refraction->SetRender();

	STATE->AlphaBegin();
	DC->DrawIndexed(_indices.size(), 0, 0);
	STATE->AlphaEnd();
}

void Water::Debug()
{
	_refraction->DeBug();
	Transform::Debug();
}

void Water::SetReflection()
{
	_reflection->SetPreRender();
}

void Water::SetRefraction()
{
	_refraction->SetPreRender();
}

void Water::CreateMesh()
{
	float left	 = -_size.x * 0.5f;
	float right  = +_size.x * 0.5f;
	float bottom = -_size.y * 0.5f;
	float top	 = +_size.y * 0.5f;

	_vertices =
	{
		{Vector3(left,	0.0f, top	), Vector2(0,0)},
		{Vector3(right, 0.0f, top	), Vector2(1,0)},
		{Vector3(left,  0.0f, bottom), Vector2(0,1)},
		{Vector3(right, 0.0f, bottom), Vector2(1,1)}
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};
}


