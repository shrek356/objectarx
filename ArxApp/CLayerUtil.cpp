#include "stdafx.h"
#include "CLayerUtil.h"


void CLayerUtil::Add(const TCHAR* layer_name, Adesk::UInt16 color_index)
{
	assert(layer_name != nullptr);
	assert(color_index >= 1 && color_index <= 255);


	AcDbLayerTable* p_layer_tbl = nullptr;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(p_layer_tbl, AcDb::kForWrite);
	if (!p_layer_tbl->has(layer_name))
	{
		AcDbLayerTableRecord* p_layer_tbl_rcd = new AcDbLayerTableRecord();
		p_layer_tbl_rcd->setName(layer_name);
		AcCmColor color;
		color.setColorIndex(color_index);
		p_layer_tbl_rcd->setColor(color);
		p_layer_tbl->add(p_layer_tbl_rcd);
		p_layer_tbl_rcd->close();
	}
	p_layer_tbl->close();

}

AcDbObjectId CLayerUtil::GetLayerId(const TCHAR* layer_name)
{
	assert(layer_name != nullptr);
	AcDbLayerTable* p_layer_tbl = nullptr;
	AcDbObjectId layer_id = AcDbObjectId::kNull;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(p_layer_tbl, AcDb::kForRead);
	if (p_layer_tbl->has(layer_name))
	{
		p_layer_tbl->getAt(layer_name, layer_id);
	}
	p_layer_tbl->close();
	return layer_id;
}



bool CLayerUtil::SetColor(const TCHAR* layer_name, Adesk::UInt16 color_index)
{
	assert(layer_name != nullptr);
	assert(color_index >= 1 && color_index <= 255);
	bool b_ret = false;
	const AcDbObjectId layer_id = GetLayerId(layer_name);
	AcDbLayerTableRecord* p_layer_tbl_rcd = nullptr;
	if (acdbOpenObject(p_layer_tbl_rcd, layer_id, AcDb::kForWrite) == Acad::eOk)
	{
		AcCmColor color;
		color.setColorIndex(color_index);
		p_layer_tbl_rcd->setColor(color);
		b_ret = true;
		p_layer_tbl_rcd->close();
	}

	return b_ret;
}

void CLayerUtil::GetLayerList(AcDbObjectIdArray& layers)
{
	AcDbLayerTable* p_layer_tbl = nullptr;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(p_layer_tbl, AcDb::kForRead);
	AcDbLayerTableIterator* it = nullptr;
	p_layer_tbl->newIterator(it);
	AcDbLayerTableRecord* p_layer_tbl_rcd = nullptr;
	for (it->start(); !it->done(); it->step())
	{
		if (it->getRecord(p_layer_tbl_rcd) == Acad::eOk)
		{
			layers.append(p_layer_tbl_rcd->objectId());
			p_layer_tbl_rcd->close();
		}
	}
	delete it;
	p_layer_tbl->close();
}


void CLayerUtil::Delete(const TCHAR* layer_name)
{
	assert(layer_name != nullptr);
	const AcDbObjectId layer_id = CLayerUtil::GetLayerId(layer_name);
	if (layer_id.isValid())
	{
		AcDbLayerTableRecord* p_layer_tbl_rcd = nullptr;
		if (acdbOpenObject(p_layer_tbl_rcd, layer_id, AcDb::kForWrite) == Acad::eOk)
		{
			p_layer_tbl_rcd->erase();
			p_layer_tbl_rcd->close();
		}
	}
	else
	{
		acutPrintf(L"\n no layer name existing");
	}

}

