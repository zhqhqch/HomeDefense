/*
 * Checkpoint.cpp
 *
 *  Created on: 2015年3月9日
 *      Author: hqch
 */


#include "Checkpoint.h"
#include "../cocos2d/external/json/document.h"

USING_NS_CC;

Checkpoint::Checkpoint(std::string data) {

	rapidjson::Document d;
	d.Parse<0>(data.c_str());
	if (d.HasParseError()) {
		CCLOG("GetParseError %s\n",d.GetParseError());
	}

	if (!d.IsObject())
		return;

	id = d["checkPointID"].GetInt();
}
