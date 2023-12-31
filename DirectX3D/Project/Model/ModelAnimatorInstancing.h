#pragma once
class ModelAnimatorInstancing : public ModelAnimator
{
public:
	ModelAnimatorInstancing(string name);
	~ModelAnimatorInstancing();

	void Update();
	void Render();

	void Debug();

	Transform* Add();

	void PlayClip(UINT instanceIndex, int clip, float speed = 1.0f, float takeTime = 0.1f);

	Matrix GetTransformByNode(UINT instanceIndex, int nodeIndex);

private:
	void UpdateFrame(UINT instanceIndex);
	void UpdateTransforms();

private:
	vector<Transform*> _transfroms;

	vector<InstanceData> _instanceDatas;

	VertexBuffer* _instanceBuffer;

	UINT _drawCount = 0;

	FrameInstancingBuffer* _frameInstancingBuffer;

	string _name;
};