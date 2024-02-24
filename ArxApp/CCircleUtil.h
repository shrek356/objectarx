#pragma once
class CCircleUtil
{
public:
	static AcDbObjectId Add(const AcGePoint3d& center_point, const AcGeVector3d& normal, double radius);

	static AcDbObjectId Add(const AcGePoint3d& center_point, double radius);
	static AcDbObjectId Add(const AcGePoint2d& first_point, const AcGePoint2d& second_point);
	static AcDbObjectId Add(const AcGePoint2d& first_point, const AcGePoint2d& second_point,
	                        const AcGePoint2d& third_point);
};
