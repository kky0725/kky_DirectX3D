#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
{
	float left	 = -size.x * 0.5f;
	float right  = +size.x * 0.5f;
	float bottom = -size.y * 0.5f;
	float top	 = +size.y * 0.5f;

	_vertices =
	{
		{Vector3(left,	top,	0.0f), Vector2(0,0), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(right, top,	0.0f), Vector2(1,0), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(left,  bottom, 0.0f), Vector2(0,1), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(right, bottom, 0.0f), Vector2(1,1), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)}
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"NormalMapping");
	//_material->SetDiffuseMap(L"Landscape/Box.png");
}

Quad::Quad(wstring file)
{
	_material = new Material();
	_material->SetShader(L"NormalMapping");
	_material->SetDiffuseMap(file);

	Vector2 size = _material->GetDiffuseMap()->GetSize();

	float left = -size.x * 0.5f;
	float right = +size.x * 0.5f;
	float bottom = -size.y * 0.5f;
	float top = +size.y * 0.5f;

	_vertices =
	{
		{Vector3(left,	top,	0.0f), Vector2(0,0), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(right, top,	0.0f), Vector2(1,0), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(left,  bottom, 0.0f), Vector2(0,1), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)},
		{Vector3(right, bottom, 0.0f), Vector2(1,1), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f , 0.0f, 0.0f)}
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh = new Mesh(_vertices, _indices);
}

Quad::~Quad()
{
	delete _mesh;
}

void Quad::Update()
{
	Transform::Update();
}

void Quad::Render()
{
	Transform::SetWorld();

	_material->SetMaterial();
	_mesh->SetMesh();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::RenderInstanced(UINT instanceCount)
{
	Transform::SetWorld();


	_material->SetMaterial();
	_mesh->SetMesh();

	DC->DrawIndexedInstanced(_indices.size(), instanceCount, 0, 0, 0);
}
