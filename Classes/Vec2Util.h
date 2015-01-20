/*
 * Vec2Util.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef VEC2UTIL_H_
#define VEC2UTIL_H_

#include "cocos2d.h"

class Vec2Util {
public:
	static cocos2d::Vec2 add(cocos2d::Vec2 point, cocos2d::Vec2 value);
	static cocos2d::Vec2 subtract(cocos2d::Vec2 point, cocos2d::Vec2 value);
	static cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 start1, cocos2d::Vec2 start2,
			cocos2d::Vec2 end1, cocos2d::Vec2 end2);
    static cocos2d::Vec2 getTargetPoint(cocos2d::Point p, float len, float rotation);
};


#endif /* VEC2UTIL_H_ */
