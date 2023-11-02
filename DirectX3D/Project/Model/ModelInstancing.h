#pragma once
class ModelInstancing : public Model
{
public:
	ModelInstancing(string name);
	~ModelInstancing();

	void Update();
	void Render();

	void Debug();

	Transform* Add();

private:
	vector<Transform*> _transfroms;

	vector<InstanceData> _instanceDatas;

	VertexBuffer* _instanceBuffer;

	UINT _drawCount = 0;


	string _name;
};