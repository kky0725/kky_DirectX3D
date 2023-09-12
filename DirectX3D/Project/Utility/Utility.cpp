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
