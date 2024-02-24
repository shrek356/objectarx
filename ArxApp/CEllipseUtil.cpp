#include "stdafx.h"
#include "CEllipseUtil.h"


AcDbObjectId CEllipseUtil::Add(const AcGePoint3d& center_point, const AcGeVector3d& vec_normal, const AcGeVector3d& major_axis, double ratio)
{
	return CDwgDatabaseUtil::PostToModelSpace(new AcDbEllipse(center_point, vec_normal, major_axis, ratio));
}

AcDbObjectId CEllipseUtil::Add(const AcGePoint2d& first_corner_point, const AcGePoint2d& second_corner_point)
{
	return Add(
		CGePointUtil::GetMiddlePoint(CConvertUtil::ToPoint3D(first_corner_point), CConvertUtil::ToPoint3D(second_corner_point)),
		AcGeVector3d(0, 0, 1), 
		AcGeVector3d(fabs(first_corner_point.x - second_corner_point.x) / 2, 0, 0), 
		fabs(first_corner_point.y - second_corner_point.y) / (first_corner_point.x - second_corner_point.x)
	);
}
