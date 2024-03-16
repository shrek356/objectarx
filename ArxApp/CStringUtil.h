#pragma once
class CStringUtil
{
	static void Split(const CString& text, const TCHAR* sparator, std::vector<CString>& result, bool b_add_empty_item);
	static  CString Join(const std::vector<CString>& items, const TCHAR* separator);
};