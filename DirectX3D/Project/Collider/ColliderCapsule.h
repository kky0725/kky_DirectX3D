#pragma once
class ColliderCapsule : public Collider
{
public:
	ColliderCapsule();
	virtual ~ColliderCapsule();

	virtual bool Collision(IN Ray& ray, OUT Contact* contact) override;
	virtual bool Collision(ColliderBox* other) override;
	virtual bool Collision(ColliderSphere* other) override;
	virtual bool Collision(ColliderCapsule* other) override;

private:
	virtual void CreateMesh() override;

};