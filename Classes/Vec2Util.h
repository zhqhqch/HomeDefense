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
	static cocos2d::Vec2 add(cocos2d::Vec2 add1, cocos2d::Vec2 value);
    static cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c, cocos2d::Vec2 d);
};


#endif /* VEC2UTIL_H_ */
