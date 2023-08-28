#pragma once
class ImageCube : public Transform
{
public:
	ImageCube();
	~ImageCube();

	void Render();

	void CreateFaces();
	void CreateFace(Vector3 roation);
private:
	vector<Quad*> _faces;
	Vector2 _size = {};
};