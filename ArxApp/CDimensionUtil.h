#pragma once
class CDimensionUtil
{

public:
	static AcDbObjectId AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const TCHAR* dim_text = nullptr, const AcDbObjectId& dim_style = AcDbObjectId::kNull);
	static AcDbObjectId AddDimAligned(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const AcGeVector3d& offset_vec = AcGeVector3d::kIdentity, const TCHAR* dim_text = nullptr);
	static AcDbObjectId AddDimRotated(const AcGePoint3d& first_point, const AcGePoint3d& second_point, const AcGePoint3d& point_on_line, const double rotation, const TCHAR* dim_text = nullptr, const AcDbObjectId& dim_style = AcDbObjectId::kNull);
	static AcDbObjectId AddDimRadial(const AcGePoint3d& center_point, const AcGePoint3d& point_on_chord, double leader_length, const TCHAR* dim_text = nullptr, const AcDbObjectId& dim_style = AcDbObjectId::kNull);
	static AcDbObjectId AddDimRadial(const AcGePoint3d& center_point, double radius, double angle, double leader_length = 5);
	static AcDbObjectId AddDimDiametric(const AcGePoint3d& first_point_on_chord, const AcGePoint3d& second_point_on_chord, const double leader_length, const TCHAR* dim_text = nullptr, const AcDbObjectId& dim_style = AcDbObjectId::kNull);
	static AcDbObjectId AddDimDiametric(const AcGePoint3d& center_point, const double radius, const double angle, const double leader_length = 5);
	static AcDbObjectId AddDim2LineAngular(const AcGePoint3d& first_line_start, const AcGePoint3d& first_line_end,
		const AcGePoint3d& second_line_start, const AcGePoint3d& second_line_end,
		const AcGePoint3d& point_on_arc,
		const TCHAR* dim_text,
		const AcDbObjectId& dim_style);


	static AcDbObjectId AddDim3PointAngular(const AcGePoint3d& center_point, const AcGePoint3d& first_end_point, const AcGePoint3d& second_end_point,
		const AcGePoint3d& point_on_arc,
		const TCHAR* dim_text = nullptr,
		const AcDbObjectId& dim_style = AcDbObjectId::kNull);

	static AcDbObjectId AddDimOrdinate(Adesk::Boolean xAxis, const AcGePoint3d& start_point, const AcGePoint3d& end_point, const TCHAR* dim_text = nullptr, const AcDbObjectId& dim_style = AcDbObjectId::kNull);
	static  AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d& point_def, const AcGePoint3d& point_text_x, const AcGePoint3d& point_text_y);
	static  AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d& point_def, const AcGeVector3d& vec_offset_x, const AcGeVector3d& vec_offset_y);
};



