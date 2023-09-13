#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:

	static class  VertexShader* GetVS(wstring file);
	static class   PixelShader* GetPS(wstring file);
	static class ComputeShader* GetCS(wstring file);

	static void Delete();

	virtual void SetShader() abstract;

protected:
	ID3DBlob* _blob;

	static map<wstring, Shader*> _shaders;
};