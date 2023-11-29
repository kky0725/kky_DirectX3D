#pragma once
class HullShader : public Shader
{
	friend class Shader;
public:
	HullShader(wstring file);
	~HullShader();

	virtual void SetShader() override;
private:
	ID3D11HullShader* _shader;

};

