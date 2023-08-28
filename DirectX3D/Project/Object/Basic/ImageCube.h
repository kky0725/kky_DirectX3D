#pragma once
class ImageCube : public Transform
{
public:
	ImageCube();
	~ImageCube();

	virtual void Update();
	void Render();

	void CreateFaces();
	void CreateFace(Vector3 rotation, Vector3 translation);

	void Move();

	void Debug();

private:
	vector<Quad*> _faces;
	float _size = 1.0f;

	static int _count;
	string _label = "";
};