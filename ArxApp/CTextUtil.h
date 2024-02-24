#pragma once
class CTextUtil
{
public:
	static  AcDbObjectId AddText(const AcGePoint3d& point_insert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double rotation = 0);
	static AcDbObjectId AddMText(const AcGePoint3d& point_insert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double width = 10);



};

