/*
 * Vec2Util.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "Vec2Util.h"

USING_NS_CC;


const float PIF = 3.141592654;
const float KmPerDegree = 111.12000071117;
const float DegreesPerKm = 1.0 / KmPerDegree;
const float RadiansPerDegree = (PIF / 180.0);
const float DegreesPerRadian = (180.0 / PIF);
const float HalfPI = PIF / 2;
const float TwoPI = PIF * 2;


Vec2 Vec2Util::add(Vec2 add1, Vec2 value){
	Vec2 retVec2 = Vec2(add1.x, add1.y);
	if(value.x != 0){
		retVec2.x += value.x;
	}
	if(value.y != 0){
		retVec2.y += value.y;
	}

	return retVec2;
}

Vec2 Vec2Util::getIntersectPoint(Vec2 a, Vec2 b, Vec2 c, Vec2 d){
    float x = ((b.x - a.x) * (c.x - d.x) * (c.y - a.y) -
                      c.x * (b.x - a.x) * (c.y - d.y) + a.x * (b.y - a.y) * (c.x - d.x)) /
                    ((b.y - a.y) * (c.x - d.x) - (b.x - a.x) * (c.y - d.y));
    float y = ((b.y - a.y) * (c.y - d.y) * (c.x - a.x) - c.y
                      * (b.y - a.y) * (c.x - d.x) + a.y * (b.x - a.x) * (c.y - d.y))
                    / ((b.x - a.x) * (c.y - d.y) - (b.y - a.y) * (c.x - d.x));
    
    return Vec2(x, y);
}
