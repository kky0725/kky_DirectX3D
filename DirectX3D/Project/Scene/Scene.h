#pragma once

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() abstract;

	virtual void PreRender() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;

	virtual void Initialize() {};
	virtual void Release() {};

};