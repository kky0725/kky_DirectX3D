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


