#pragma once

namespace Utility
{
	wstring GetExtension(wstring path);

	string ToString(wstring str);
	wstring ToWstring(string str);

	wstring GetProjectDir();
	wstring GetTextureDir();

	wstring GetTextDataDir();
}