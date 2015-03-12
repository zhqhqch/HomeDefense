/*
 * Checkpoint.cpp
 *
 *  Created on: 2015年3月9日
 *      Author: hqch
 */


#include "Checkpoint.h"
#include "../cocos2d/external/json/document.h"
#include "Constants.h"
#include "Util.h"

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

	const rapidjson::Value &itemArr = d["item"];
	if(itemArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < itemArr.Size(); i++) {
			const rapidjson::Value &item = itemArr[i];
			ItemData * itemData = new ItemData();
			itemData->imageName = item["itemImageName"].GetString();
			itemData->score = item["itemScore"].GetInt();
			itemData->weight = item["itemWeight"].GetInt();
			itemData->isBox = item["itemBox"].GetBool();
			itemData->isAnimation = item["itemAnimation"].GetBool();

			itemArray.pushBack(itemData);
		}
	}

	const rapidjson::Value &positionArr = d["position"];
	if(positionArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < positionArr.Size(); i++) {
			const rapidjson::Value &position = positionArr[i];
			PositionData * positionData = new PositionData();
			positionData->positionX = position["itemPositionX"].GetDouble();
			positionData->positionY = position["itemPositionY"].GetDouble();
			positionData->rotation = position["itemRotation"].GetDouble();
			int layerType = position["itemLayerNum"].GetInt();
			if(layerType == kInnterType){
				innterPositionArray.pushBack(positionData);
			} else if(layerType == kMiddleType){
				middlePositionArray.pushBack(positionData);
			} else if(layerType == kOuterType){
				outerPositionArray.pushBack(positionData);
			}
		}
	}

	const rapidjson::Value &innterArr = d["innter"];
	if(innterArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < innterArr.Size(); i++) {
			const rapidjson::Value &innter = innterArr[i];
			ShowData * innterData = new ShowData();
			innterData->imageName = innter["imageName"].GetString();
			innterData->count = innter["count"].GetInt();

			innterArray.pushBack(innterData);
		}
	}

	const rapidjson::Value &middleArr = d["middle"];
	if(middleArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < middleArr.Size(); i++) {
			const rapidjson::Value &middle = middleArr[i];
			ShowData * middleData = new ShowData();
			middleData->imageName = middle["imageName"].GetString();
			middleData->count = middle["count"].GetInt();

			middleArray.pushBack(middleData);
		}
	}

	const rapidjson::Value &outerArr = d["outer"];
	if(outerArr.IsArray()){
		for (rapidjson::SizeType i = 0; i < outerArr.Size(); i++) {
			const rapidjson::Value &outer = outerArr[i];
			ShowData * outerData = new ShowData();
			outerData->imageName = outer["imageName"].GetString();
			outerData->count = outer["count"].GetInt();

			outerArray.pushBack(outerData);
		}
	}
}


Vector<Checkpoint::RockData *> Checkpoint::getShowRockByType(int type) {
	Vector<ShowData *> showArr;
	Vector<PositionData *> positionArr;
	if(type == kInnterType){
		showArr = innterArray;
		positionArr = innterPositionArray;
	} else if(type == kMiddleType){
		showArr = middleArray;
		positionArr = middlePositionArray;
	} else if(type == kOuterType){
		showArr = outerArray;
		positionArr = outerPositionArray;
	}

	Vector<RockData *> rockArray;

	for(ShowData *showData : showArr){
		ItemData *itemData = getItemByImageName(showData->imageName);
		Vector<Checkpoint::PositionData *> posArr = getRandomPosition(positionArr, showData->count);
		for(PositionData * pos : posArr){
			RockData *rock = new RockData();
			rock->imageName = itemData->imageName;
			rock->positionX = pos->positionX;
			rock->positionY = pos->positionY;
			rock->rotation = pos->rotation;
			rock->score = itemData->score;
			rock->weight = itemData->weight;
			rock->isBox = itemData->isBox;
			rock->isAnimation = itemData->isAnimation;

			rockArray.pushBack(rock);
		}
	}

	return rockArray;
}


Checkpoint::ItemData * Checkpoint::getItemByImageName(std::string imageName) {
	for(ItemData *itemData : itemArray){
		if(itemData->imageName == imageName){
			return itemData;
		}
	}

	return nullptr;
}

Vector<Checkpoint::PositionData *> Checkpoint::getRandomPosition(Vector<PositionData *>positionArr, int quantity) {
	int * order = Util::randomOrder(10, quantity);
	Vector<Checkpoint::PositionData *> retArr;
	for (int i=0;i<quantity;i++) {
		retArr.pushBack(positionArr.at(order[i]));
	}

	free(order);

	return retArr;
}
