#pragma once
class RawBuffer
{
public:
	RawBuffer(void* inputData, UINT byteWidth);
	~RawBuffer();

	void Copy(void* data, UINT size);


	ID3D11UnorderedAccessView* GetUAV() { return _uav; }
private:
	void CrateOutput();
	void CreateUAV();
	void CreateResult();

private:
	ID3D11UnorderedAccessView* _uav;

	ID3D11Resource* _output;
	ID3D11Resource* _result;

	void* _inputData;
	UINT _byteWidth;
};