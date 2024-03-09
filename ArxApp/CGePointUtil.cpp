#include "stdafx.h"
#include "CGePointUtil.h"

AcGePoint3d CGePointUtil::GetMiddlePoint(const AcGePoint3d& start_point, const AcGePoint3d& end_point)
{
	return AcGePoint3d{
		(start_point.x + end_point.x) / 2,
		(start_point.y + end_point.y) / 2,
		(start_point.z + end_point.z) / 2
	};
}

AcGePoint2d CGePointUtil::GetMiddlePoint(const AcGePoint2d& start_point, const AcGePoint2d& end_point)
{
	return AcGePoint2d{
		(start_point.x + end_point.x) / 2,
		(start_point.y + end_point.y) / 2
	};
}


AcGePoint3d CGePointUtil::PolarPoint(const AcGePoint3d& base_point, double angle, double length)
{
	return AcGePoint3d{
		base_point.x+length*cos(angle),
		base_point.y+length*sin(angle),
		base_point.z
	};
}



AcGePoint3d CGePointUtil::RelativePoint(const AcGePoint3d& base_point, double x, double y)
{
	return AcGePoint3d{
		base_point.x+x,
		base_point.y+y,
		base_point.z
	};
}
