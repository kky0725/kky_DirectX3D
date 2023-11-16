#pragma once
class Spark : public Particle
{
private:
	struct VertexParticle
	{
		Vector3 position = {};
		Vector2 size	 = {};
		Vector3 velocity = {};
	};

public:
	Spark(wstring file, bool isAdditive = false);
	virtual ~Spark();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;

	virtual void Play(Vector3 position) override;

private:
	virtual void SetVertex() override;

	void UpdateParticle();

private:
	FloatValueBuffer* _valueBuffer;
	FloatValueBuffer* _startColorBuffer;
	FloatValueBuffer* _endColorBuffer;
	
	float _minRadius = 5.0f;
	float _maxRaidus = 10.0f;

	float _minSize = 0.1f;
	float _maxSize = 1.0f;

	vector<VertexParticle> _vertices;
};