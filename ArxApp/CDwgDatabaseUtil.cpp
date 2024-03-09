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


AcDbObjectIdArray CDwgDatabaseUtil::GetEntityId(const TCHAR* layer_name)
{
	AcDbObjectIdArray ent_ids;
	bool b_filter_layer = false;
	AcDbObjectId layer_id;

	if (layer_name != nullptr)
	{
		AcDbLayerTable* p_layer_table = nullptr;
		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(p_layer_table, AcDb::kForRead);
		if (!p_layer_table->has(layer_name))
		{
			p_layer_table->close();
			return ent_ids;
		}

		p_layer_table->getAt(layer_name, layer_id);
		p_layer_table->close();
		b_filter_layer = true;
	}
	AcDbBlockTable* p_block_table;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(p_block_table, AcDb::kForRead);

	AcDbBlockTableRecord* p_block_table_record = nullptr;
	p_block_table->getAt(ACDB_MODEL_SPACE, p_block_table_record, AcDb::kForRead);
	p_block_table->close();


	AcDbBlockTableRecordIterator* it = nullptr;
	p_block_table_record->newIterator(it);

	for (it->start(); !it->done(); it->step())
	{
		AcDbEntity* p_ent = nullptr;
		Acad::ErrorStatus es = it->getEntity(p_ent, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			if (b_filter_layer)
			{
				if (p_ent->layerId() == layer_id)
				{
					ent_ids.append(p_ent->objectId());
				}
			}
			else
			{
				ent_ids.append(p_ent->objectId());
			}
			p_ent->close();
		}
		else
		{
			acutPrintf(L"\n CDwgDatabaseUtil::GetEntityId can not open entity,error code as %d", static_cast<int>(es));
		}



	}
	delete it;
	p_block_table_record->close();

	return ent_ids;

}
