#pragma once
class ModelClip
{
	friend class ModelAnimator;
	friend class ModelAnimatorInstancing;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

	void SetEndEvent(function<void(void)> EndEvent, float ratio)
	{
		this->_EndEvent = EndEvent;
		this->_ratio = ratio;
	}

private:
	string name ="";
	UINT frameCount = 0;
	float tickPerSecond = 0.0f;
	float duration = 0.0f;

	unordered_map<string, KeyFrame*> _keyFrames = {};

	function<void()> _EndEvent;

	float _ratio;
};