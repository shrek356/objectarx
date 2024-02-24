#include "stdafx.h"
#include "CHatchUtil.h"


AcDbObjectId CHatchUtil::Add(const AcDbObjectIdArray& loop_ids, const TCHAR* pattern_name, double pattern_scale)
{

	AcDbHatch* p_hatch = new AcDbHatch;
	p_hatch->setNormal(AcGeVector3d(0, 0, 1));
	p_hatch->setElevation(0);
	p_hatch->setAssociative(true);
	p_hatch->setPatternScale(pattern_scale);
	p_hatch->setPattern(AcDbHatch::kPreDefined, pattern_name);

	ErrorStatus es = p_hatch->appendLoop(AcDbHatch::kExternal, loop_ids);
	es = p_hatch->evaluateHatch();

	const AcDbObjectId hatch_id = CDwgDatabaseUtil::PostToModelSpace(p_hatch);


	if(acdbOpenObject(p_hatch,hatch_id,AcDb::kForRead)==Acad::eOk)
	{
		AcDbObjectIdArray assoc_ent_ids;
		p_hatch->getAssocObjIds(assoc_ent_ids);
		for (const auto& id : assoc_ent_ids)
		{
			AcDbEntity* p_ent = nullptr;
			if (acdbOpenObject(p_ent, id, AcDb::kForWrite) == Acad::eOk)
			{
				p_ent->addPersistentReactor(hatch_id);
				p_ent->close();
			}
		}
		p_hatch->close();
	}
	return hatch_id;
}
