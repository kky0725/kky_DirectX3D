#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	virtual void SetShader() override;

private:
	ID3D11PixelShader* _pixelShader;

};
