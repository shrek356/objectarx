#pragma once

class CGePointUtil
{
public:
	static AcGePoint3d GetMiddlePoint(const AcGePoint3d& start_point, const AcGePoint3d& end_point);
	static AcGePoint2d GetMiddlePoint(const AcGePoint2d& start_point, const AcGePoint2d& end_point);
	static AcGePoint3d PolarPoint(const AcGePoint3d& base_point, double angle, double length);
	static  AcGePoint3d RelativePoint(const AcGePoint3d& base_point, double x, double y);
};
  