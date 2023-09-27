#pragma once

namespace Utility
{
	wstring GetExtension(wstring path);

	 string ToString(wstring str);
	wstring ToWstring(string str);

	wstring GetProjectDir();
	wstring GetTextureDir();
	wstring GetTextDataDir();

	bool StartsWith(string str, string start);
	bool StartsWith(wstring str, wstring start);
}