#pragma once
class Model : public Transform
{
public:
	Model(string name);
	~Model();

	virtual void Update();
	void Render();


private:
	ModelReader* _reader;
	MatrixBuffer* _worldBuffer;

	vector<ModelVertex> _vertices;
	vector<UINT>		_indices;
};