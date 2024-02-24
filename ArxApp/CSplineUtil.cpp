#include "stdafx.h"
#include "CSplineUtil.h"

AcDbObjectId CSplineUtil::Add(const AcGePoint3dArray& points, int order, double fitToTolerance)
{
	assert(order >= 2 && order <= 26);
	return	CDwgDatabaseUtil::PostToModelSpace(
		new AcDbSpline(points, order, fitToTolerance)
	);
}

AcDbObjectId CSplineUtil::Add(const AcGePoint3dArray& points, const AcGeVector3d& start_tangent, const AcGeVector3d& end_tangent, int order, double fitToTolerance)
{
	assert(order >= 2 && order <= 26);
	return	CDwgDatabaseUtil::PostToModelSpace(
		new AcDbSpline(points,start_tangent,end_tangent, order, fitToTolerance)
	);
}
