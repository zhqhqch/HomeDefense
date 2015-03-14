/*
 * Util.h
 *
 *  Created on: 2015年3月12日
 *      Author: hqch
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "cocos2d.h"

class Util {
public:
	static int * randomOrder(int total, int quantity);

	static cocos2d::ValueVector split(const char* srcStr, const char* sSep);
};


#endif /* UTIL_H_ */
