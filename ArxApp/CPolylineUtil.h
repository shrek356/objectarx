#pragma once
class CPolylineUtil
{
public:
	static AcDbObjectId Add(const AcGePoint2dArray& points, double width);
	static AcDbObjectId Add(const AcGePoint2d& start_point, const AcGePoint2d& end_point, double width);
	static AcDbObjectId Add(const AcGePoint3dArray& points);
	static 	AcDbObjectId AddPolygon(const AcGePoint2d& center_point, int edge_numbers, double circum_circle_radius, double rotation, double width);
	static  AcDbObjectId AddRectangle(const AcGePoint2d& first_point, const AcGePoint2d& second_point,double line_width);
	static  AcDbObjectId AddPolyCircle(const AcGePoint2d& center_Point, double radius, double line_width);
	static  AcDbObjectId AddPolyArc(const AcGePoint2d& center_point, double radius, double start_angle, double end_angle, double line_width);
};

