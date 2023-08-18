#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Cube* _cube;

};

