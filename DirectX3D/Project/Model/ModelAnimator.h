#pragma once
class ModelAnimator
{
public:
	ModelAnimator();
	~ModelAnimator();

	void ReadClip(string file, UINT clipIndex = 0);

private:
	ModelReader* _reader;
	vector<ModelClip> _clips;
};