#pragma once
class DomainShader : public Shader
{
	friend class Shader;
public:
	DomainShader(wstring file);
	~DomainShader();

	virtual void SetShader() override;
private:
	ID3D11DomainShader* _shader;

};
