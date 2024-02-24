#include "stdafx.h"


AcDbObjectIdArray CRegionUtil::Add(const AcDbObjectIdArray& curve_ids)
{
	AcDbObjectIdArray region_ids{0};
	AcDbVoidPtrArray curves{0};
	AcDbVoidPtrArray regions{0};
	AcDbEntity* p_ent = nullptr;
	for (const auto& id : curve_ids)
	{
		acdbOpenAcDbEntity(p_ent, id, AcDb::kForRead);
		if (p_ent->isKindOf(AcDbCurve::desc()))
			curves.append(p_ent);
	}

	const Acad::ErrorStatus error_status = AcDbRegion::createFromCurves(curves, regions);

	if (error_status == Acad::eOk)
	{
		for (const auto region : regions)
		{

			AcDbRegion* p_region=static_cast<AcDbRegion*>(region);
			p_region->setDatabaseDefaults();
			region_ids.append(CDwgDatabaseUtil::PostToModelSpace(p_region));
		}
	}
	else
	{
		for (const auto& region : regions)
		{
			delete static_cast<AcRxObject*>(region);
		}

	}

	for ( const auto& curve : curves)
	{
		static_cast<AcDbEntity*>(curve)->close();
	}

	return region_ids;
}
