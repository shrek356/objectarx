#include "stdafx.h"
#include "CArcUtil.h"

AcDbObjectId CArcUtil::Add(const AcGePoint3d& center_point, const AcGeVector3d& vec, double radius, double start_angle,
	double end_angle)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbArc(center_point, vec, radius, start_angle, end_angle)
	);
}


AcDbObjectId CArcUtil::Add(const AcGePoint2d& center_point, double radius, double start_angle, double end_angle)
{
	return Add(CConvertUtil::ToPoint3D(center_point),
		AcGeVector3d(0, 0, 1),
		radius,
		start_angle,
		end_angle);
}

AcDbObjectId CArcUtil::Add(const AcGePoint2d& start_point, const AcGePoint2d& point_on_arc, const AcGePoint2d& end_point)
{
	const AcGeCircArc2d geArc(start_point, point_on_arc, end_point);
	const AcGePoint2d  center_point = geArc.center();
	const double radius = geArc.radius();

	const  AcGeVector2d vec_start = AcGeVector2d(start_point.x - center_point.x, start_point.y - center_point.y);
	const AcGeVector2d vec_end = AcGeVector2d(end_point.x - center_point.x, end_point.y - center_point.y);

	const double start_angle = vec_start.angle();
	const double end_angle = vec_end.angle();

	return Add(center_point, radius, start_angle, end_angle);

}
AcDbObjectId CArcUtil::AddByPointsOfStartCenterEnd(const AcGePoint2d& start_point, const AcGePoint2d& center_point, const AcGePoint2d& end_point)
{
	const double radius = start_point.distanceTo(center_point);

	const AcGeVector2d& vec_start = AcGeVector2d(start_point.x - center_point.x, start_point.y - center_point.y);
	const AcGeVector2d& vec_end = AcGeVector2d(end_point.x - center_point.x, end_point.y - center_point.y);

	return Add(center_point, radius, vec_start.angle(), vec_end.angle());
}

AcDbObjectId CArcUtil::Add(const AcGePoint2d& start_point, const AcGePoint2d& center_point, const double angle)
{

	double radius = start_point.distanceTo(center_point);

	const AcGeVector2d start_vec = AcGeVector2d(start_point.x - center_point.x, start_point.y - center_point.y);
	const	double start_angle = start_vec.angle();
	const	double end_angle = start_angle + angle;

	return Add(center_point, radius, start_angle, end_angle);

}
