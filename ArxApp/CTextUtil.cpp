#include "stdafx.h"
#include "CTextUtil.h"

AcDbObjectId CTextUtil::AddText(const AcGePoint3d& point_insert, const TCHAR* text, AcDbObjectId style, double height, double rotation)
{
	AcDbText* p_text = new AcDbText(point_insert, text, style, height, rotation);
	return CDwgDatabaseUtil::PostToModelSpace(p_text);

}


AcDbObjectId CTextUtil::AddMText(const AcGePoint3d& point_insert, const TCHAR* text, AcDbObjectId style, double height, double width)
{
	AcDbMText* p_mText = new AcDbMText;
	p_mText->setTextStyle(style);
	p_mText->setContents(text);
	p_mText->setLocation(point_insert);
	p_mText->setTextHeight(height);
	p_mText->setWidth(width);
	p_mText->setAttachment(AcDbMText::kBottomLeft);
	return CDwgDatabaseUtil::PostToModelSpace(p_mText);
}
