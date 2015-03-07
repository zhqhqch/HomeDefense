/*
 * EncyptUtil.h
 *
 *  Created on: 2015年3月7日
 *      Author: hqch
 */

#ifndef ENCYPTUTIL_H_
#define ENCYPTUTIL_H_

#include "cocos2d.h"

class EncyptUtil {

public:
	static std::string encrypt(const std::string& content);
	static std::string decrypt(const std::string& content);
};


#endif /* ENCYPTUTIL_H_ */
