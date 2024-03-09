#pragma once
class CBlockUtil
{
public:
	static AcDbObjectId InsertBockRef(const AcDbObjectId& blk_def_id, const AcGePoint3d& insert_point, double scale, double rotation);
	static void SetScaleFactor(AcDbBlockReference* p_blk_ref, double scale);
	static  AcDbObjectId GetBlkDefIdByName(const TCHAR* blk_def_name);
	static AcDbObjectId InsertBlockReferenceWithAttribute(const AcDbObjectId& blk_def_id, const AcGePoint3d& insert_point, double scale, double rotation);
	static void AppendAttributeToBlockReference(AcDbBlockReference* p_blk_ref, AcDbAttributeDefinition* p_attr_def);
	static bool SetBlockReferenceAttribute(AcDbBlockReference* p_blk_ref, const TCHAR* tag, const TCHAR* value);
	static bool GetBlockReferenceAttributeValue(AcDbBlockReference* p_blk_ref, const TCHAR* tag, AcString& tag_value);
	static void CheckIntersectionBetweenBlockAndEntity(AcDbBlockReference* p_blk_ref, AcDbEntity* p_ent, 
		AcGePoint3dArray& int_points,
		bool b_intersection_with_text=true, 
		bool b_project_to_XOY=false, 
		bool b_extend_ent_arg=false);
};


