#include "stdafx.h"
#include "CStringUtil.h"

void CStringUtil::Split(const CString& text, const TCHAR* separator, std::vector<CString>& result, bool b_add_empty_item)
{
	double prev = 0, current = 0;
	CString str_copy_text = text;
	str_copy_text.TrimRight(TEXT(" "));

	if(str_copy_text.Find(separator,0)<0)
	{
		if(str_copy_text.GetLength()>0)
		{
			result.push_back(str_copy_text);
		}
		return;
	}

	const double length = str_copy_text.GetLength();
	bool b_exit = false;
	while(true)
	{
		current = str_copy_text.Find(separator, prev);
		if(current==-1)
		{
			current = length;
			b_exit = true;
		}

		CString item = str_copy_text.Mid(prev, current - prev);

		if(b_add_empty_item || item.GetLength()>0)
		{
			result.push_back(item);
		}
		if(b_exit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}

}

CString CStringUtil::Join(const std::vector<CString>& items, const TCHAR* separator)
{
	CString str_result;
	for(const auto& item :items)
	{
		str_result += item + separator;
	}
	str_result.TrimRight(separator);
	return  str_result;
}
