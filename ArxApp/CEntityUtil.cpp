#include "stdafx.h"
#include "CEntityUtil.h"


void CEntityUtil::SetColor(const AcDbObjectId& ent_id, Adesk::UInt16 color_index)
{
	assert(color_index > 0 && color_index <= 256);

	AcDbEntity* p_ent = nullptr;

	if (acdbOpenObject(p_ent, ent_id, AcDb::kForWrite) == Acad::eOk)
	{
		p_ent->setColorIndex(color_index);
		p_ent->close();
	}
}


Acad::ErrorStatus CEntityUtil::Move(AcDbObjectId ent_id, const AcGePoint3d& base_point, const AcGePoint3d& dest_point)
{
	AcGeMatrix3d xform;
	xform.setToTranslation(
		AcGeVector3d(dest_point.x - base_point.x, dest_point.y - base_point.y, dest_point.z - base_point.z)
	);

	AcDbEntity* pEnt = nullptr;

	Acad::ErrorStatus es = acdbOpenObject(pEnt, ent_id, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}

	return es;
}

Acad::ErrorStatus CEntityUtil::Rotate(AcDbObjectId ent_id, const AcGePoint2d& base_point, double rotation)
{
	AcGeMatrix3d xform;
	xform.setToRotation(rotation, AcGeVector3d(0, 0, 1), CConvertUtil::ToPoint3D(base_point));

	AcDbEntity* pEnt = nullptr;

	Acad::ErrorStatus es = acdbOpenObject(pEnt, ent_id, AcDb::kForWrite,false);
	if(es==Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}

	return es;
}

Acad::ErrorStatus CEntityUtil::Scale(AcDbObjectId ent_id, const AcGePoint3d& base_point, double scale_factor)
{
	AcGeMatrix3d xform;
	xform.setToScaling(scale_factor, base_point);

	AcDbEntity* pEnt = nullptr;

	Acad::ErrorStatus es = acdbOpenObject(pEnt, ent_id, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}

	return es;
	
}

