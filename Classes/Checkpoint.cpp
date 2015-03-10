/*
 * Checkpoint.cpp
 *
 *  Created on: 2015年3月9日
 *      Author: hqch
 */


#include "Checkpoint.h"
#include "../cocos2d/external/json/document.h"

USING_NS_CC;

Checkpoint::Checkpoint(int checkpointID) {
	char fileName[20];
	sprintf(fileName, "checkpoint-%d.json", checkpointID);

	rapidjson::Document d;
	std::string str = FileUtils::getInstance()->getStringFromFile(fileName);

	d.Parse<0>(str.c_str());

	if(d.HasParseError()){
		log("GetParseError %s\n", d.GetParseError());
	}
	if(!d.IsObject()){
		return;
	}

	id = d["checkPointID"].GetInt();
	layer1Speed = d["layer1Speed"].GetDouble();
	layer2Speed = d["layer2Speed"].GetDouble();
	layer3Speed = d["layer3Speed"].GetDouble();
	layer4Speed = d["layer4Speed"].GetDouble();



}
