/*
 * Checkpoint.h
 *
 *  Created on: 2015年3月9日
 *      Author: hqch
 */

#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_


#include "cocos2d.h"

class Checkpoint {
public:
	class BgData : public cocos2d::Ref {
	public:
		std::string imageName;
		float positionX;
		float positionY;
		float rotation;
		int layerNum;
	};

	class ItemData : public cocos2d::Ref {
	public:
		std::string imageName;
		int score;
		int weight;
		bool isBox;
		bool isAnimation;
	};

	class PositionData : public cocos2d::Ref {
		public:
			float positionX;
			float positionY;
			float rotation;
			int layerNum;
	};

	class ShowData : public cocos2d::Ref {
		public:
			std::string imageName;
			int count;
	};

	class RockData : public cocos2d::Ref {
	public:
		std::string imageName;
		float positionX;
		float positionY;
		float rotation;
		int score;
		int weight;
		bool isBox;
		bool isAnimation;
	};

public:
	Checkpoint(int checkpointID);

	int id;
	float layer1Speed;
	float layer2Speed;
	float layer3Speed;
	float layer4Speed;

	cocos2d::Vector<BgData *> bgArray;
	cocos2d::Vector<ItemData *> itemArray;
	cocos2d::Vector<PositionData *> innterPositionArray;
	cocos2d::Vector<PositionData *> middlePositionArray;
	cocos2d::Vector<PositionData *> outerPositionArray;

	cocos2d::Vector<ShowData *> innterArray;
	cocos2d::Vector<ShowData *> middleArray;
	cocos2d::Vector<ShowData *> outerArray;

	//获取指定层级上显示的矿石信息
	cocos2d::Vector<RockData *> getShowRockByType(int type);

private:
	//根据图片名称获取对应的信息
	ItemData * getItemByImageName(std::string imageName);

	//获取随机的指定个数的位置信息
	cocos2d::Vector<PositionData *> getRandomPosition(cocos2d::Vector<PositionData *>positionArr, int quantity);
};


#endif /* CHECKPOINT_H_ */
