#pragma once
class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();


	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;
private:
	TextureCube* _textureCube = nullptr;
	Cube* _cube = nullptr;

	Sphere* _sphere;

};