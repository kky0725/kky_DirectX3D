#pragma once
class Particle
{
public:
	Particle();
	virtual ~Particle();

	virtual void Update() {}
	virtual void Render();
	virtual void Debug() {}

	virtual void Play(Vector3 position);

	void Stop();

	virtual void SetVertex() = 0;

protected:
	Material*		_material;
	VertexBuffer*	_vertexBuffer;
	GeometryShader* _geometryShader;

	const UINT MAX_COUNT = 1000;
	UINT _drawCount = MAX_COUNT;

	bool _isAdditive = false;

	bool _isActive = false;

	Vector3 _postition;
};
