#pragma once
class Sprite : public Particle
{
public:
	Sprite(wstring file, Vector2 size, float frameX, float frameY, bool isAdditive = false, UINT maxFrameCount = 0);
	virtual ~Sprite();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;

	virtual void Play(Vector3 position) override;

private:
	virtual void SetVertex() override;

private:
	FloatValueBuffer* _buffer;

	vector<VertexTexture> _vertex;

	float _time = 0.0f;
	float _speed = 1.0f;

	UINT _curFrameCount = 0;
	UINT _maxFrameCount = 0;

	Vector2 _size;
};