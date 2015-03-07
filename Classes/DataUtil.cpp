/*
 * DataUtil.cpp
 *
 *  Created on: 2015年3月7日
 *      Author: hqch
 */


#include "DataUtil.h"
#include "EncyptUtil.h"

USING_NS_CC;

void DataUtil::saveInt(const char* key, int value) {
	char a[3];
	sprintf(a,"%d",value);
	std::string s = EncyptUtil::encrypt(a);
	UserDefault::getInstance()->setStringForKey(key, s);
	UserDefault::getInstance()->flush();
}

int DataUtil::getIntForKey(const char* key) {
	std::string s = UserDefault::getInstance()->getStringForKey(key);
	s = EncyptUtil::decrypt(s);
	int value;
	sscanf(const_cast<char*>(s.c_str()),"%d",&value);
	return value;
}
