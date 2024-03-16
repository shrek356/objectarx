#include "stdafx.h"
#include "CConvertUtil.h"

AcGePoint3d CConvertUtil::ToPoint3D(const AcGePoint2d& point2d, double z)
{
	return AcGePoint3d{ point2d.x, point2d.y, z };
}
CString CConvertUtil::ToString(int value)
{
	CString str;
	str.Format(L"%d", value);
	return str;
}
