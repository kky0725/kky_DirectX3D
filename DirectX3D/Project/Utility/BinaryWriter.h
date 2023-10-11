#pragma once
class BinaryWriter
{
public:
	BinaryWriter(wstring file);
	~BinaryWriter();
	
	void WriteData(    int data);
	void WriteData(   UINT data);
	void WriteData(  float data);
	void WriteData( string data);
	void WriteData(wstring data);
	void WriteData(Vector3 data);
	void WriteData(Vector4 data);
	void WriteData(  void* data, UINT dataSize);
	void WriteData(XMFLOAT4X4 data);

private:
	HANDLE _file = nullptr;
	DWORD  _size = 0;
};