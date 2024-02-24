#pragma once
class CArcUtil
{
public:
	static AcDbObjectId Add(const AcGePoint3d& center_point, const AcGeVector3d& vec, double radius, double start_angle,
		double end_angle);
	static AcDbObjectId Add(const AcGePoint2d& center_point, double radius, double start_angle, double end_angle);
	static AcDbObjectId Add(const AcGePoint2d& start_point, const AcGePoint2d& point_on_arc, const AcGePoint2d& end_point);
	static AcDbObjectId AddByPointsOfStartCenterEnd(const AcGePoint2d& start_point, const AcGePoint2d& center_point, const AcGePoint2d& end_point);
	static AcDbObjectId Add(const AcGePoint2d& start_point, const AcGePoint2d& center_point, const double angle);
};
