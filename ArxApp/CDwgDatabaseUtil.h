#pragma once
class CDwgDatabaseUtil
{
public:
	static AcDbObjectId PostToModelSpace(AcDbEntity* p_ent);
	static AcDbObjectIdArray GetEntityId(const TCHAR* layer_name=nullptr);
};
