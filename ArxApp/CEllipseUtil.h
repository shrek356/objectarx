#pragma once
class CEllipseUtil
{
public:
	static  AcDbObjectId Add(const AcGePoint3d& center_point, const AcGeVector3d& vec_normal, const AcGeVector3d& major_axis, double ratio);
	static AcDbObjectId Add(const AcGePoint2d& first_corner_point, const AcGePoint2d& second_corner_point);

};

