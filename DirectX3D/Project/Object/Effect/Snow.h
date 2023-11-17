#pragma once
class Snow : public Particle
{
private:
	struct VertexParticle
	{
		Vector3 pos = {};
		Vector2 size = {};
		Vector2 random = {};
	};

public:
	Snow(wstring file = L"Effect/Snow.png");
	virtual ~Snow();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;

private:
	virtual void SetVertex() override;


private:
	vector<VertexParticle> _vertices;
	WeatherBuffer* _buffer;

};