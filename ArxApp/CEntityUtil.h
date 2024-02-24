#pragma once
#include "StdAfx.h"

class CEntityUtil
{
public:
	static void SetColor(const AcDbObjectId& ent_id, Adesk::UInt16 color_index);
	static Acad::ErrorStatus Rotate(AcDbObjectId ent_id, const AcGePoint2d& base_point, double rotation);
	static Acad::ErrorStatus Move(AcDbObjectId ent_id, const AcGePoint3d& base_point,const AcGePoint3d& dest_point);
	static Acad::ErrorStatus Scale(AcDbObjectId ent_id, const AcGePoint3d& base_point,double scale_factor);


};
