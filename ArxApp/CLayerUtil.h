#pragma once
class CLayerUtil
{
public:
	static void Add(const TCHAR* layer_name,Adesk::UInt16 color_index=18);
	static void Delete(const TCHAR* layer_name);
	static AcDbObjectId GetLayerId(const TCHAR* layer_name);
	static bool SetColor(const TCHAR* layer_name, Adesk::UInt16 color_index);
	static void GetLayerList(AcDbObjectIdArray& layers);
	
};

