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
    rockCount = d["rockCount"].GetInt();
	layer1Speed = d["layer1Speed"].GetDouble();
	layer2Speed = d["layer2Speed"].GetDouble();
	layer3Speed = d["layer3Speed"].GetDouble();
	layer4Speed = d["layer4Speed"].GetDouble();

	const rapidjson::Value &bgArr = d["bg"];
	if(bgArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < bgArr.Size(); i++) {
			const rapidjson::Value &bg = bgArr[i];
			BgData * bgData = new BgData();
			bgData->imageName = bg["bgImageName"].GetString();
			bgData->positionX = bg["bgPositionX"].GetDouble();
			bgData->positionY = bg["bgPositionY"].GetDouble();
			bgData->rotation = bg["bgRotation"].GetDouble();
			bgData->layerNum = bg["bgLayerNum"].GetInt();

			bgArray.pushBack(bgData);
		}
	}

	const rapidjson::Value &rockArr = d["rock"];
	if(rockArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < rockArr.Size(); i++) {
			const rapidjson::Value &rock = rockArr[i];
			RockData * rockData = new RockData();
			rockData->imageName = rock["rockImageName"].GetString();
			rockData->positionX = rock["rockPositionX"].GetDouble();
			rockData->positionY = rock["rockPositionY"].GetDouble();
			rockData->rotation = rock["rockRotation"].GetDouble();
			rockData->score = rock["rockScore"].GetInt();
			rockData->weight = rock["rockWeight"].GetInt();

			rockArray.pushBack(rockData);
		}
	}
}
