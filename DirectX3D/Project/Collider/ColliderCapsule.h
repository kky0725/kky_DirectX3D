#pragma once
class ColliderCapsule : public Collider
{
	friend class ColliderBox;
public:
	ColliderCapsule(float radius = 1.0f, float height = 2.0f, UINT stackCount = 15, UINT sliceCount = 30);
	virtual ~ColliderCapsule();

	virtual bool Collision(IN Ray& ray, OUT Contact* contact) override;
	virtual bool Collision(ColliderBox* other) override;
	virtual bool Collision(ColliderSphere* other) override;
	virtual bool Collision(ColliderCapsule* other) override;

	float Radius() { return radius * max(_globalScale.x, max(_globalScale.y, _globalScale.z)); }
	float Height() { return height * _globalScale.y; }

private:
	virtual void CreateMesh() override;

	float radius;
	float height;

	UINT stackCount;
	UINT sliceCount;
};