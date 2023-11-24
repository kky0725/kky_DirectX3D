#pragma once
class Water : public Transform
{
public:
	Water(wstring normalFile, float width = 100.0f, float height = 100.0f);
	virtual ~Water();

	virtual void Update();
	void Render();
	virtual void Debug();

	void SetReflection();
	void SetRefraction();

private:
	void CreateMesh();

private:
	Vector2 _size;

	Mesh*	  _mesh;
	Material* _material;

	vector<VertexTexture> _vertices;
	vector<UINT>		   _indices;

	Reflection* _reflection;
	Refraction* _refraction;
};