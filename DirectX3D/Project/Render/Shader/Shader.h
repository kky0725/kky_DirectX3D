#pragma once
class Shader
{
protected:
	Shader();
	virtual ~Shader();

public:

	static class VertexShader* GetVS(wstring file);
	static class  PixelShader* GetPS(wstring file);

	static void Delete();

	virtual void SetShader() abstract;

protected:
	ID3DBlob* _blob;

	static unordered_map<wstring, Shader*> _shaders;
};