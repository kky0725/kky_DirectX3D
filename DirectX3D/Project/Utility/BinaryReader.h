#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring file);
	~BinaryReader();

	int		ReadInt();
	UINT	ReadUINT();
	float	ReadFloat();
	string	ReadString();
	wstring ReadWString();
	Vector3 ReadVector3();
	Vector4 ReadVector4();
	XMFLOAT4X4 ReadXMFLOAT4X4();

	void ReadData(OUT void** data, UINT dataSize);

	bool Succeeded();

private:
	HANDLE _file = nullptr;
	DWORD  _size = 0;
};