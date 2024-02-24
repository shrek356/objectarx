#pragma once
class CSplineUtil
{
public:
	static  AcDbObjectId Add(const AcGePoint3dArray& points, int order = 4, double fitToTolerance = 0.0);
	static  AcDbObjectId Add(const AcGePoint3dArray& points, const AcGeVector3d& start_tangent, const AcGeVector3d& end_tangent, int order=4, double fitToTolerance=0.0);
};

