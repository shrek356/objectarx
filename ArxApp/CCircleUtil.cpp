#include "stdafx.h"
#include "CCircleUtil.h"


AcDbObjectId CCircleUtil::Add(const AcGePoint3d& center_point, const AcGeVector3d& normal, double radius)
{
	return CDwgDatabaseUtil::PostToModelSpace(new AcDbCircle{center_point, normal, radius});
}

AcDbObjectId CCircleUtil::Add(const AcGePoint3d& center_point, double radius)
{
	return Add(center_point, AcGeVector3d(0, 0, 1), radius);
}

AcDbObjectId CCircleUtil::Add(const AcGePoint2d& first_point, const AcGePoint2d& second_point)
{
	const AcGePoint2d center_point = CGePointUtil::GetMiddlePoint(first_point, second_point);
	const double radius = AcGePoint3d(center_point.x, center_point.y, 0).distanceTo(
		AcGePoint3d(first_point.x, first_point.y, 0));
	return Add(AcGePoint3d(center_point.x, center_point.y, 0), radius);
}

AcDbObjectId CCircleUtil::Add(const AcGePoint2d& first_point, const AcGePoint2d& second_point,
	const AcGePoint2d& third_point)
{
	const AcGeCircArc2d geArc(first_point, second_point, third_point);
	return Add(AcGePoint3d(geArc.center().x, geArc.center().y, 0), geArc.radius());
}