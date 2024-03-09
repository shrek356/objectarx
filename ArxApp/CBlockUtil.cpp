#include "stdafx.h"
#include "CBlockUtil.h"

AcDbObjectId CBlockUtil::InsertBockRef(const AcDbObjectId& blk_def_id, const AcGePoint3d& insert_point, double scale, double rotation)
{
	AcDbBlockReference* p_block_ref = new AcDbBlockReference(insert_point, blk_def_id);
	p_block_ref->setRotation(rotation);
	SetScaleFactor(p_block_ref, scale);
	return CDwgDatabaseUtil::PostToModelSpace(p_block_ref);
}

void CBlockUtil::SetScaleFactor(AcDbBlockReference* p_blk_ref, double scale)
{
	assert(p_blk_ref);
	p_blk_ref->setScaleFactors(AcGeScale3d(scale, scale, scale));
}

AcDbObjectId CBlockUtil::GetBlkDefIdByName(const TCHAR* blk_def_name)
{
	AcDbBlockTable* p_blk_tbl = nullptr;
	Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(p_blk_tbl, AcDb::kForRead);
	AcDbObjectId blk_id = nullptr;
	es = p_blk_tbl->getAt(blk_def_name, blk_id);
	p_blk_tbl->close();
	if (es == Acad::eOk)
	{
		return blk_id;
	}
	else
	{
		return AcDbObjectId::kNull;
	}

}


AcDbObjectId CBlockUtil::InsertBlockReferenceWithAttribute(const AcDbObjectId& blk_def_id, const AcGePoint3d& insert_point, double scale, double rotation)
{
	AcDbBlockReference* p_blk_ref = new AcDbBlockReference(insert_point, blk_def_id);

	SetScaleFactor(p_blk_ref, rotation);

	AcDbBlockTableRecord* p_blk_def_rcd = nullptr;

	if (Acad::eOk == acdbOpenObject(p_blk_def_rcd, p_blk_ref->blockTableRecord(), AcDb::kForRead))
	{
		if (p_blk_def_rcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator* it = nullptr;
			p_blk_def_rcd->newIterator(it);

			for (it->start(); !it->done(); it->step())
			{
				AcDbEntity* p_ent = nullptr;
				if (it->getEntity(p_ent) == Acad::eOk)
				{
					AcDbAttributeDefinition* p_attr_def = AcDbAttributeDefinition::cast(p_ent);
					if (p_attr_def != nullptr)
					{
						AppendAttributeToBlockReference(p_blk_ref, p_attr_def);
					}
					p_ent->close();
				}
			}
			delete it;
		}
		p_blk_def_rcd->close();
	}
	return CDwgDatabaseUtil::PostToModelSpace(p_blk_ref);
}

void CBlockUtil::AppendAttributeToBlockReference(AcDbBlockReference* p_blk_ref, AcDbAttributeDefinition* p_attr_def)
{
	AcDbAttribute* p_attr = new AcDbAttribute;

	p_attr->setPropertiesFrom(p_blk_ref);
	p_attr->setLayer(p_blk_ref->layerId());


	p_attr->setInvisible(p_attr_def->isInvisible());
	p_attr->setPosition(p_attr_def->position());
	p_attr->setHeight(p_attr_def->height());
	p_attr->setWidthFactor(p_attr->widthFactor());
	p_attr->setRotation(p_attr_def->rotation());
	p_attr->setHorizontalMode(p_attr->horizontalMode());
	p_attr->setVerticalMode(p_attr_def->verticalMode());
	p_attr->setAlignmentPoint(p_attr_def->alignmentPoint());
	p_attr->setTextStyle(p_attr_def->textStyle());
	p_attr->setAttributeFromBlock(p_blk_ref->blockTransform());


	TCHAR* p_str = p_attr_def->tag();
	p_attr->setTag(p_str);
	acutDelString(p_str);
	p_attr->setFieldLength(p_attr_def->fieldLength());
	p_attr->setTextString(p_attr_def->textString());


	p_blk_ref->appendAttribute(p_attr);
	p_attr->close();
}


bool CBlockUtil::SetBlockReferenceAttribute(AcDbBlockReference* p_blk_ref, const TCHAR* tag, const TCHAR* tag_value)
{
	AcDbBlockTableRecord* p_blk_def_rcd = nullptr;
	bool b_ret = true;

	if (Acad::eOk == acdbOpenObject(p_blk_def_rcd, p_blk_ref->blockTableRecord(), AcDb::kForRead))
	{
		if (p_blk_def_rcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator* it;
			p_blk_def_rcd->newIterator(it);
			for (it->start(); !it->done(); it->step())
			{
				AcDbEntity* p_ent = nullptr;

				it->getEntity(p_ent);
				AcDbAttributeDefinition* p_attr_def = AcDbAttributeDefinition::cast(p_ent);
				if (p_attr_def != nullptr)
				{
					TCHAR* p_sz_tag = p_attr_def->tag();
					CString str_tag = p_sz_tag;
					acutDelString(p_sz_tag);
					if (str_tag.CompareNoCase(tag) == 0)
					{
						bool b_found = false;

						AcDbObjectIterator* attr_it = p_blk_ref->attributeIterator();

						for (attr_it->start(); !attr_it->done(); attr_it->step())
						{
							AcDbAttribute* p_attr = nullptr;
							Acad::ErrorStatus es = acdbOpenObject(p_attr, attr_it->objectId(), AcDb::kForWrite);
							if (Acad::eOk == es)
							{
								p_sz_tag = p_attr->tag();
								str_tag = p_sz_tag;
								acutDelString(p_sz_tag);
								if (str_tag.CompareNoCase(tag) == 0)
								{
									p_attr->setTextString(tag_value);
									b_found = true;
								}
								p_attr->close();
							}
						}
						delete attr_it;
						if (!b_found)
						{
							AppendAttributeToBlockReference(p_blk_ref, p_attr_def);
						}
					}
				}
				p_ent->close();
			}
			delete it;
		}
		else
		{
			b_ret = false;
		}
		p_blk_def_rcd->close();
	}

	return b_ret;
}
bool CBlockUtil::GetBlockReferenceAttributeValue(AcDbBlockReference* p_blk_ref, const TCHAR* tag, AcString& tag_value)
{
	bool b_found = false;

	AcDbObjectIterator* it = p_blk_ref->attributeIterator();
	if (it)
	{
		while (!it->done())
		{
			const AcDbObjectId attr_id = it->objectId();
			AcDbAttribute* p_attr = nullptr;
			if (p_blk_ref->openAttribute(p_attr, attr_id, AcDb::kForRead) == Acad::eOk)
			{
				TCHAR* sz_tag = p_attr->tag();
				AcString str_tag = tag;
				str_tag.makeUpper();
				if (_tcscmp(str_tag, sz_tag) == 0)
				{
					TCHAR* sz_value = p_attr->textString();
					tag_value = sz_value;
					acutDelString(sz_value);
					b_found = true;
				}
				acutDelString(sz_tag);
				p_attr->close();

			}
			it->step();
		}
		delete it;
		return  b_found;
	}
	else
	{
		return false;
	}
}

void CBlockUtil::CheckIntersectionBetweenBlockAndEntity(AcDbBlockReference* p_blk_ref, AcDbEntity* p_ent, AcGePoint3dArray& int_points,
	bool b_intersection_with_text, bool b_project_to_XOY, bool b_extend_ent_arg)
{
	assert(p_ent);
	assert(p_blk_ref);

	AcGeMatrix3d x_form = p_blk_ref->blockTransform();
	const AcDbObjectId blk_ref_tbl_id = p_blk_ref->blockTableRecord();
	AcDbBlockTableRecord* p_blk_tbl_rcd = nullptr;
	if (Acad::eOk == acdbOpenObject(p_blk_tbl_rcd, blk_ref_tbl_id, AcDb::kForRead))
	{
		AcDbBlockTableRecordIterator* it = nullptr;
		p_blk_tbl_rcd->newIterator(it);
		for (it->start(); !it->done(); it->step())
		{
			AcDbEntity* p_sub_ent = nullptr;
			if (it->getEntity(p_sub_ent) == Acad::eOk)
			{
				if ((!b_intersection_with_text) &&
					(p_sub_ent->isKindOf(AcDbText::desc()) ||
						p_sub_ent->isKindOf(AcDbMText::desc())))
				{
					p_sub_ent->close();
					continue;
				}
				AcDbEntity* p_copied_ent = nullptr;
				if (p_sub_ent->getTransformedCopy(x_form, p_copied_ent) == Acad::eOk)
				{
					const AcDb::Intersect int_mode = b_extend_ent_arg ? AcDb::kExtendArg : AcDb::kOnBothOperands;
					if (b_project_to_XOY)
					{
						p_copied_ent->intersectWith(p_ent, int_mode, AcGePlane::kXYPlane, int_points);
					}
					else
					{
						p_copied_ent->intersectWith(p_ent, int_mode, int_points);
					}
					delete p_copied_ent;
				}
				p_sub_ent->close();
			}
		}
		delete it;
		p_blk_tbl_rcd->close();

	}


}
