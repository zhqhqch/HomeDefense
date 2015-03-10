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

	class RockData : public cocos2d::Ref {
	public:
		std::string imageName;
		float positionX;
		float positionY;
		float rotation;
		int score;
		int weight;
	};

public:
	Checkpoint(int checkpointID);

	int id;
    int rockCount;
	float layer1Speed;
	float layer2Speed;
	float layer3Speed;
	float layer4Speed;

	cocos2d::Vector<BgData *> bgArray;
	cocos2d::Vector<RockData *> rockArray;
};


#endif /* CHECKPOINT_H_ */
