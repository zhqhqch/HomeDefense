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
	char a[4];
	sprintf(a,"%d",checkpointID);

	char fileName[30];
	strcpy(fileName, "checkpoint-") ;
	const char* suffix = ".json";
	strcat(fileName, a);
	strcat(fileName, suffix);

	//*** 读取 json 文件 ***
	rapidjson::Document readdoc;
	std::string data = FileUtils::getInstance()->getStringFromFile(fileName);
	readdoc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());

	log("data====%s", data.c_str());

	if(readdoc.HasParseError()){
		log("GetParseError%s\n", readdoc.GetParseError());
	}

	if (!readdoc.IsObject())
		return;

	rapidjson::Value& _json = readdoc["checkPointID"];
	id = _json.GetInt();
}
