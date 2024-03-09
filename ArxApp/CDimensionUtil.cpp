#include "stdafx.h"
#include "CDimensionUtil.h"


AcDbObjectId CDimensionUtil::AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return  CDwgDatabaseUtil::PostToModelSpace(
		new AcDbAlignedDimension{
			first_point,
			second_point,
			point_on_line,
			dim_text,
			dim_style
		}
	);
}

AcDbObjectId CDimensionUtil::AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const AcGeVector3d& offset_vec, const TCHAR* dim_text)
{
	AcDbObjectId dim_id = CDwgDatabaseUtil::PostToModelSpace(
		new AcDbAlignedDimension{
			first_point,
			second_point,
			point_on_line,
			dim_text,
			AcDbObjectId::kNull
		}
	);

	AcDbAlignedDimension* p_dim = nullptr;
	if (acdbOpenObject(p_dim, dim_id, AcDb::kForWrite) == Acad::eOk)
	{
		p_dim->setDimtmove(1);
		p_dim->setTextPosition(p_dim->textPosition() + offset_vec);
		p_dim->close();
	}

	return dim_id;
}

AcDbObjectId CDimensionUtil::AddDimRotated(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const double rotation, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbRotatedDimension{
			rotation,
			first_point,
			second_point,
			point_on_line,
			dim_text,
			dim_style
		}
	);
}


AcDbObjectId CDimensionUtil::AddDimRadial(const AcGePoint3d& center_point, const AcGePoint3d& point_on_chord, double leader_length, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbRadialDimension{
			center_point,
			point_on_chord,
			leader_length,
			dim_text,
			dim_style
		}
	);
}
AcDbObjectId CDimensionUtil::AddDimRadial(const AcGePoint3d& center_point, double radius, double angle, double leader_length)
{

	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbRadialDimension{
			center_point,
			CGePointUtil::PolarPoint(center_point,angle,radius),
			leader_length
		}
	);
}


AcDbObjectId CDimensionUtil::AddDimDiametric(const AcGePoint3d& first_point_on_chord, const AcGePoint3d& second_point_on_chord, const double leader_length, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbDiametricDimension{
			first_point_on_chord,
			second_point_on_chord,
			leader_length,
			dim_text,
			dim_style
		}
	);
}

AcDbObjectId CDimensionUtil::AddDimDiametric(const AcGePoint3d& center_point, const double radius, const double angle, const double leader_length)
{
	return AddDimDiametric(
		CGePointUtil::PolarPoint(center_point, angle, radius),
		CGePointUtil::PolarPoint(center_point, angle + CMathUtil::PI(), radius),
		leader_length
	);
}

AcDbObjectId CDimensionUtil::AddDim2LineAngular(const AcGePoint3d& first_line_start, const AcGePoint3d& first_line_end,
	const AcGePoint3d& second_line_start, const AcGePoint3d& second_line_end, const AcGePoint3d& point_on_arc,
	const TCHAR* dim_text,
	const AcDbObjectId& dim_style)
{

	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDb2LineAngularDimension{
			first_line_start,
			first_line_end,
			second_line_start,
			second_line_end,
			point_on_arc,
			dim_text,
			dim_style
		}
	);

}

AcDbObjectId CDimensionUtil::AddDim3PointAngular(const AcGePoint3d& center_point, const AcGePoint3d& first_end_point, const AcGePoint3d& second_end_point, const AcGePoint3d& point_on_arc, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDb3PointAngularDimension{
			center_point,
			first_end_point,
			second_end_point,
			point_on_arc,
			dim_text,
			dim_style
		}
	);
}

AcDbObjectId CDimensionUtil::AddDimOrdinate(Adesk::Boolean xAxis, const AcGePoint3d& start_point, const AcGePoint3d& end_point, const TCHAR* dim_text, const AcDbObjectId& dim_style)
{
	return CDwgDatabaseUtil::PostToModelSpace(
		new AcDbOrdinateDimension{
			xAxis,
			start_point,
			end_point,
			dim_text,
			dim_style
		}
	);
}


AcDbObjectIdArray CDimensionUtil::AddDimOrdinate(const AcGePoint3d& point_def, const AcGePoint3d& point_text_x, const AcGePoint3d& point_text_y)
{
	AcDbObjectIdArray dim_ids;

	dim_ids.append(AddDimOrdinate(Adesk::kTrue, point_def, point_text_x));
	dim_ids.append(AddDimOrdinate(Adesk::kFalse, point_def, point_text_y));

	return dim_ids;
}

AcDbObjectIdArray CDimensionUtil::AddDimOrdinate(const AcGePoint3d& point_def, const AcGeVector3d& vec_offset_x, const AcGeVector3d& vec_offset_y)
{
	return AddDimOrdinate(point_def, point_def + vec_offset_x, point_def + vec_offset_y);
}
