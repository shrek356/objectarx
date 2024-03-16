#pragma once
class CTextFileUtil
{
	static void Save(const TCHAR* file_name, const std::vector<CString>& lines);
	static void Load(const TCHAR* file_name, std::vector<CString> lines);
};

