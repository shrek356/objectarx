#include "stdafx.h"
#include "CPolylineUtil.h"

#include "CEntityUtil.h"


AcDbObjectId CPolylineUtil::Add(const AcGePoint2dArray& points, double width)
{
	AcDbPolyline* pPoly_line = new AcDbPolyline(points.length());
	for (int i = 0; i < points.length(); i++)
	{
		pPoly_line->addVertexAt(i, points.at(i), 0, width,width);

	}
	return CDwgDatabaseUtil::PostToModelSpace(pPoly_line);
}

AcDbObjectId CPolylineUtil::Add(const AcGePoint2d& start_point, const AcGePoint2d& end_point, double width)
{
	AcGePoint2dArray points;
	points.append(start_point);
	points.append(end_point);
	return Add(points, width);
}

AcDbObjectId CPolylineUtil::Add(const AcGePoint3dArray& points)
{
	AcGePoint3dArray verts = points;
	return CDwgDatabaseUtil::PostToModelSpace(new AcDb3dPolyline(AcDb::k3dSimplePoly, verts));
}

AcDbObjectId CPolylineUtil::AddPolygon(const AcGePoint2d& center_point, int edge_numbers, double circum_circle_radius, double rotation, double width)
{
	double angle = 2 * CMathUtil::PI() / (double)edge_numbers;
	AcGePoint2dArray pts;
	for (int i = 0; i < edge_numbers; i++)
	{
		pts.append(AcGePoint2d(
			center_point.x + circum_circle_radius * cos(i * angle),
			center_point.y + circum_circle_radius * sin(i * angle)
		));
	}
	AcDbObjectId poly_id = Add(pts, width);

	AcDbEntity* pEnt = nullptr;

	if (acdbOpenObject(pEnt, poly_id, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbPolyline* pPolyline = AcDbPolyline::cast(pEnt);
		if (pPolyline != nullptr)
		{
			pPolyline->setClosed(Adesk::kTrue);
		}
		pEnt->close();
	}
	CEntityUtil::Rotate(poly_id, center_point, rotation);
	return poly_id;
}

AcDbObjectId CPolylineUtil::AddRectangle(const AcGePoint2d& first_point, const AcGePoint2d& second_point, double line_width)
{
	double x1 = first_point.x, x2 = second_point.x;
	double y1 = first_point.y, y2 = second_point.y;
	const AcGePoint2d left_bottom_point = AcGePoint2d(min(x1, x2), min(y1, y2));
	const AcGePoint2d right_bottom_poit = AcGePoint2d(max(x1, x2), min(y1, y2));
	const AcGePoint2d right_top_point = AcGePoint2d(max(x1, x2), max(y1, y2));
	const AcGePoint2d left_top_point = AcGePoint2d(min(x1, x2), max(y1, y2));

	AcDbPolyline* pPoly_line = new AcDbPolyline(4);
	pPoly_line->addVertexAt(0, left_bottom_point, 0, line_width,line_width);
	pPoly_line->addVertexAt(1, right_bottom_poit, 0, line_width, line_width);
	pPoly_line->addVertexAt(2, right_top_point, 0, line_width, line_width);
	pPoly_line->addVertexAt(3, left_top_point, 0, line_width, line_width);
	pPoly_line->setClosed(Adesk::kTrue);
	return 	CDwgDatabaseUtil::PostToModelSpace(pPoly_line);
}

AcDbObjectId CPolylineUtil::AddPolyCircle(const AcGePoint2d& center_Point, double radius, double line_width)
{
	AcGePoint2d pts[3] = {
		{center_Point.x+radius,center_Point.y},
		{center_Point.x-radius,center_Point.y},
		{center_Point.x+radius,center_Point.y}
	};
	AcDbPolyline* pPoly_line = new AcDbPolyline(3);
	pPoly_line->addVertexAt(0, pts[0], 1, line_width, line_width);
	pPoly_line->addVertexAt(1, pts[1], 1, line_width, line_width);
	pPoly_line->addVertexAt(2, pts[2], 1, line_width, line_width);

	pPoly_line->setClosed(Adesk::kTrue);
	return CDwgDatabaseUtil::PostToModelSpace(pPoly_line);
}

AcDbObjectId CPolylineUtil::AddPolyArc(const AcGePoint2d& center_point, double radius, double start_angle, double end_angle, double line_width)
{
	AcGePoint2d first_point, second_point;
	first_point.x = center_point.x + radius * cos(start_angle);
	first_point.y = center_point.y + radius * sin(start_angle);

	second_point.x = center_point.x + radius * cos(end_angle);
	second_point.y = center_point.y + radius * sin(end_angle);

	AcDbPolyline* pPoly_line = new AcDbPolyline(2);
	pPoly_line->addVertexAt(0, first_point, tan((end_angle - start_angle) / 4), line_width, line_width);
	pPoly_line->addVertexAt(1, second_point, 0, line_width, line_width);

	return CDwgDatabaseUtil::PostToModelSpace(pPoly_line);
}
