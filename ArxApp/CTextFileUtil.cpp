#include "stdafx.h"
#include "CTextFileUtil.h"

void CTextFileUtil::Save(const TCHAR* file_name, const std::vector<CString>& lines)
{
	CStdioFile file(file_name, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	for (int i = 0; i < lines.size(); i++)
	{
		file.WriteString(lines[i]);
		file.WriteString(TEXT("\n"));
	}
	file.Close();
}

void CTextFileUtil::Load(const TCHAR* file_name, std::vector<CString> lines)
{
	lines.clear();
	CStdioFile file(file_name, CFile::modeRead | CFile::typeText);
	CString str_line;
	while(file.ReadString(str_line))
	{
		lines.push_back(str_line);
	}
}

