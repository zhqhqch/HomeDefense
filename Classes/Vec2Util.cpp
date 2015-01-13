/*
 * Vec2Util.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "Vec2Util.h"

USING_NS_CC;

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
