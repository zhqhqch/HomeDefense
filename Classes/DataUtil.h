/*
 * DataUtil.h
 *
 *  Created on: 2015年3月7日
 *      Author: hqch
 */

#ifndef DATAUTIL_H_
#define DATAUTIL_H_

#include "cocos2d.h"

class DataUtil {
public:
	static void saveInt(const char* key, int value);
	static int getIntForKey(const char* key);

	static void saveString(const char* key, const std::string& value);
	static std::string getStringForKey(const char* key);
};

#endif /* DATAUTIL_H_ */
