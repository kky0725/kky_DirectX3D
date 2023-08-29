#pragma once
class TextureCube : public Transform
{
	enum side
	{
		LEFT,
		RIGHT,
		BOTTOM,
		TOP,
		FRONT,
		BACK
	};

public:
	TextureCube();
	~TextureCube();

	void Update();
	void Render();

	void CreateQuads();

private:
	vector<Quad*> _quads;
};
