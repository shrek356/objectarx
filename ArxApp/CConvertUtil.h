#pragma once
#include "CMathUtil.h"



class CConvertUtil
{
public:
	static AcGePoint3d ToPoint3D(const AcGePoint2d& point2d, double z = 0);
	static   double AngleToRadian(const double angle) { return  angle * CMathUtil::PI() / 180; }
	static   double RadianToAngle(const double radian) { return radian * 180 / CMathUtil::PI(); }
	
};
