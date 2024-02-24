#include "stdafx.h"
#include "CLineUtil.h"


AcDbObjectId CLineUtil::Add(const AcGePoint3d& start_point, const AcGePoint3d& end_point)
{
	auto p_line = new AcDbLine(start_point, end_point);
	return CDwgDatabaseUtil::PostToModelSpace(p_line);
}
