#pragma once
class Model : public Transform
{
public:
	Model(string name, wstring shaderFile = L"NormalMapping");
	~Model();

	virtual void Update();
	void Render();
	
	ModelReader* GetReader() { return _reader; }

private:
	ModelReader* _reader;
};