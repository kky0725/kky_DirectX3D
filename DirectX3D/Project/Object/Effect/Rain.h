#pragma once
class Rain : public Particle
{
public:
	Rain(wstring file = L"Effect/Rain.png");
	virtual ~Rain();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;

private:
	virtual void SetVertex() override;

private:
	vector<VertexTexture> _vertices;

	WeatherBuffer* _buffer;

};