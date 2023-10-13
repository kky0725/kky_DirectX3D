#pragma once
class ModelClip
{
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

private:
	string name ="";
	UINT frameCount = 0;
	float tickPerSecond = 0.0f;
	float duration = 0.0f;

	unordered_map<string, KeyFrame*> _keyFrames = {};
};