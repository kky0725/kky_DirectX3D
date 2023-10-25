#pragma once

struct Ray
{
	Vector3 origion;
	Vector3 direction;
};

struct Contact
{
	Vector3 hitPoint;
	float distance;
};

class Collider : public Transform
{
public:
	enum Type
	{
		BOX, SPHERE, CAPSULE
	};

	static bool _hiddenInGame;

public:
	Collider();
	virtual ~Collider();

	bool Collision(Collider* other);

	virtual bool Collision(IN Ray& ray, OUT Contact* contact = nullptr) = 0;
	virtual bool Collision(class ColliderBox* other) = 0;
	virtual bool Collision(class ColliderSphere* other) = 0;
	virtual bool Collision(class ColliderCapsule* other) = 0;

	virtual void CreateMesh() = 0;

	void Render();

	void SetColor(float r, float g, float b) { _material->GetBuffer()->data.diffuse = { r, g, b, 1.0f }; }

protected:
	typedef Vertex VertexType;

	Material* _material;
	Mesh* _mesh;
	Type _type;

	vector<VertexType> _vertices;
	vector<UINT> _indices;
};