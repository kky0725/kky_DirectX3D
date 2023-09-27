#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
	UINT index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring str)
{
	string temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

wstring Utility::ToWstring(string str)
{
	wstring temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

wstring Utility::GetProjectDir()
{
	WCHAR path[128];
	GetCurrentDirectory(128, path);

	wstring dir = path;

	return dir + L"/";
}

wstring Utility::GetTextureDir()
{
	return GetProjectDir() + L"_Texture/";
}

wstring Utility::GetTextDataDir()
{

	return  GetProjectDir() + L"_TextData/";
}

bool Utility::StartsWith(string str, string start)
{
	string result = str.substr(0, start.size());

	return result == start;
}

bool Utility::StartsWith(wstring str, wstring start)
{
	return StartsWith(ToString(str), ToString(start));
}
