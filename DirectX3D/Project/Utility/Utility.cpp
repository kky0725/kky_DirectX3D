#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
	UINT index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}
