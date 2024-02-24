#include "stdafx.h"
#include "CDimensionUtil.h"


AcDbObjectId CDimensionUtil::AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const TCHAR* dim_text, AcDbObjectId dim_style)
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
	if(acdbOpenObject(p_dim,dim_id,AcDb::kForWrite)==Acad::eOk)
	{
		p_dim->setDimtmove(1);
		p_dim->setTextPosition(  p_dim->textPosition()+ offset_vec);
		p_dim->close();
	}

	return dim_id;
}

AcDbObjectId CDimensionUtil::AddDimRotated(const AcGePoint3d& first_point,const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const double rotation, const TCHAR* dim_text, const AcDbObjectId dim_style)
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
