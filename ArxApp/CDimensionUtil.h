#pragma once
class CDimensionUtil
{

public:
	static AcDbObjectId AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const TCHAR* dim_text = nullptr, AcDbObjectId dim_style = AcDbObjectId::kNull);
	static AcDbObjectId AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const AcGeVector3d& offset_vec=AcGeVector3d::kIdentity,const TCHAR* dim_text=nullptr);
	static AcDbObjectId AddDimRotated(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line,const double rotation, const TCHAR* dim_text=nullptr,const AcDbObjectId dim_style=AcDbObjectId::kNull);

};

