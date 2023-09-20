#pragma once
class TerrainEditor : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	TerrainEditor(UINT height = 100, UINT width = 100);
	virtual ~TerrainEditor();

	void Update();
	void Render();

	void Debug();

	Material* Getmaterial() { return _material; }

	bool Picking(OUT Vector3* position);

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();

	void AdjustHeight();

private:
	vector<VertexType>	_vertices;
	vector<UINT>		_indices;

	Material*	_material;
	Mesh*		_mesh;

	MatrixBuffer* _worldBuffer;

	UINT _width;
	UINT _height;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;

	//computeShader

	struct InputDesc
	{
		UINT index;

		Vector3 v0, v1, v2;
	};

	struct OutputDesc
	{
		int isPicked;

		float u, v;

		float distance;
	};

	StructuredBuffer* _structuredBuffer;
		   RayBuffer* _rayBuffer;

	ComputeShader* _computeShader;

	 InputDesc* _input;
	OutputDesc* _output;

	UINT _polygonCount;

	Vector3 _pickedPos;

	BrushBuffer* _brushBuffer;

	float _adjustValue = 10.0f;
};

