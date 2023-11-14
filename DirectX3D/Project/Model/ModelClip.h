#pragma once
class ModelClip
{
	friend class ModelAnimator;
	friend class ModelAnimatorInstancing;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

	void SetEndEvent(float ratio, function<void(void)> EndEvent);

	void Init();
	void Execute(float ratio);

private:
	string name ="";
	UINT frameCount = 0;
	float tickPerSecond = 0.0f;
	float duration = 0.0f;

	unordered_map<string, KeyFrame*> _keyFrames = {};

	multimap<float, function<void()>> _EndEvents;
	multimap<float, function<void()>>::iterator _eventIter;

	float _ratio;


};