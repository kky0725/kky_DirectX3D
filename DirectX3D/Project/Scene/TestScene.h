#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	ImageCube* _imageCube;
};