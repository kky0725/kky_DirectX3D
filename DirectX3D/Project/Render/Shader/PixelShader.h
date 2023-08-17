#pragma once
class PixelShader : public Shader
{
	friend class Shader;
	PixelShader(wstring file);
	~PixelShader();

public:
	virtual void SetShader() override;

private:
	ID3D11PixelShader* _pixelShader;

};
