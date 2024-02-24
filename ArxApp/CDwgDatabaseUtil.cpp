#include "stdafx.h"
#include "CDwgDatabaseUtil.h"

AcDbObjectId CDwgDatabaseUtil::PostToModelSpace(AcDbEntity* p_ent)
{
	assert(p_ent);

	AcDbBlockTable* p_block_table = nullptr;

	acdbHostApplicationServices()->workingDatabase()->getBlockTable(p_block_table, AcDb::kForRead);

	AcDbBlockTableRecord* p_block_table_record = nullptr;

	p_block_table->getAt(ACDB_MODEL_SPACE, p_block_table_record, AcDb::kForWrite); 

	p_block_table->close();

	AcDbObjectId ent_id;
	const Acad::ErrorStatus res_status = p_block_table_record->appendAcDbEntity(ent_id, p_ent);

	if (res_status != Acad::eOk)
	{
		p_block_table_record->close();
		delete p_ent;
		p_ent = nullptr;
		return AcDbObjectId::kNull;
	}

	p_block_table_record->close();
	p_ent->close();

	return ent_id;
}
