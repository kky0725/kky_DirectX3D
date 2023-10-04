#include "Framework.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(wstring path)
{
	if (!StartsWith(path, L"_"))
		path = L"_Texture/" + path;

	_file = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::~BinaryReader()
{
	CloseHandle(_file);
}

int BinaryReader::ReadInt()
{
	int data;
	assert(ReadFile(_file, &data, sizeof(int), &_size, nullptr));
	return data;
}

UINT BinaryReader::ReadUINT()
{
	UINT data;
	assert(ReadFile(_file, &data, sizeof(UINT), &_size, nullptr));
	return data;
}

float BinaryReader::ReadFloat()
{
	float data;
	assert(ReadFile(_file, &data, sizeof(float), &_size, nullptr));
	return data;
}

string BinaryReader::ReadString()
{
	UINT dataSize = ReadUINT();

	char* data = new char[dataSize + 1];

	assert(ReadFile(_file, data, sizeof(char) * dataSize, &_size, nullptr));

	data[dataSize] = '\0';

	string str = data;

	delete[] data;

	return str;
}

wstring BinaryReader::ReadWString()
{
	UINT dataSize = ReadUINT();

	wchar_t* data = new wchar_t[dataSize + 1];

	assert(ReadFile(_file, data, sizeof(wchar_t) * dataSize, &_size, nullptr));

	data[dataSize] = '\0';

	wstring str = data;

	delete[] data;

	return str;
}

Vector3 BinaryReader::ReadVector3()
{
	Vector3 data;

	data.x = ReadFloat();
	data.y = ReadFloat();
	data.z = ReadFloat();

	return data;
}

Vector4 BinaryReader::ReadVector4()
{
	Vector4 data;

	data.x = ReadFloat();
	data.y = ReadFloat();
	data.z = ReadFloat();
	data.w = ReadFloat();

	return data;
}

void BinaryReader::ReadData(OUT void** data, UINT dataSize)
{
	assert(ReadFile(_file, *data, dataSize, &_size, nullptr));
}

bool BinaryReader::Succeeded()
{
	return _file != INVALID_HANDLE_VALUE;
}
