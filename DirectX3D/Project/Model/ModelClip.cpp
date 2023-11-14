#include "Framework.h"
#include "ModelClip.h"

ModelClip::ModelClip()
{
}

ModelClip::~ModelClip()
{
	for (pair<string, KeyFrame*> frame : _keyFrames)
		delete frame.second;

	_keyFrames.clear();
}

KeyFrame* ModelClip::GetKeyFrames(string name)
{
	if (_keyFrames.count(name) == 0)
		return nullptr;

	return _keyFrames[name];
}

void ModelClip::SetEndEvent(float ratio, function<void(void)> EndEvent)
{
	_EndEvents.emplace(ratio, EndEvent);
}

void ModelClip::Init()
{
	_eventIter = _EndEvents.begin();
}

void ModelClip::Execute(float ratio)
{
	if (_EndEvents.empty()) return;

	if (_eventIter == _EndEvents.end()) return;

	if (_eventIter->first > ratio) return;

	_eventIter->second();
	_eventIter++;
}