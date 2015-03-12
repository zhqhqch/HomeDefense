/*
 * EarthLayer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "EarthLayer.h"
#include "Checkpoint.h"
#include "Constants.h"


USING_NS_CC;


Earth::Earth(Checkpoint *c){
	checkpoint = c;
	init();
}

bool Earth::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

    layer1 = Sprite::create();
    layer1->setContentSize(Size(2048, 2048));
    layer1->setPosition(w, h);
    
    layer2 = Sprite::create();
    layer2->setContentSize(Size(2048, 2048));
    layer2->setPosition(w, h);
    
    layer3 = Sprite::create();
    layer3->setContentSize(Size(2048, 2048));
    layer3->setPosition(w, h);
    
    layer4 = Sprite::create();
    layer4->setContentSize(Size(2048, 2048));
    layer4->setPosition(w, h);

    w = layer1->getContentSize().width / 2;
    h = layer1->getContentSize().height / 2;
    
	Sprite * earth1 = Sprite::createWithSpriteFrameName("earth-1.png");
	earth1->setAnchorPoint(Vec2(1, 0));
	earth1->setPosition(w, h);

	Sprite * earth2 = Sprite::createWithSpriteFrameName("earth-2.png");
	earth2->setAnchorPoint(Vec2(0, 0));
	earth2->setPosition(w, h);

	Sprite * earth3 = Sprite::createWithSpriteFrameName("earth-3.png");
	earth3->setAnchorPoint(Vec2(0, 1));
	earth3->setPosition(w, h);

	Sprite * earth4 = Sprite::createWithSpriteFrameName("earth-4.png");
	earth4->setAnchorPoint(Vec2(1, 1));
	earth4->setPosition(w, h);


	Vector<Checkpoint::BgData *> bgArr = checkpoint->bgArray;
	for(Checkpoint::BgData * bgData : bgArr){
		Sprite * sprite = Sprite::createWithSpriteFrameName(bgData->imageName);
		sprite->setRotation(bgData->rotation);
		sprite->setAnchorPoint(Vec2(0, 1));
		sprite->setPosition(bgData->positionX, bgData->positionY);

		if(bgData->layerNum == 2){
			layer2->addChild(sprite);
		} else if(bgData->layerNum == 3){
			layer3->addChild(sprite);
		} else if(bgData->layerNum == 4){
			layer4->addChild(sprite);
		}
	}


    this->addChild(layer1, 4);
    this->addChild(layer2, 2);
    this->addChild(layer3, 3);
    this->addChild(layer4, 1);
    

    int tag = 10;
    Vector<Checkpoint::RockData *> innterRockArr = checkpoint->getShowRockByType(kInnterType);
    initOre(innterRockArr);

    tag += innterRockArr.size();
    Vector<Checkpoint::RockData *> middleRockArr = checkpoint->getShowRockByType(kMiddleType);
    initOre(middleRockArr);

    tag += middleRockArr.size();
	Vector<Checkpoint::RockData *> outerRockArr = checkpoint->getShowRockByType(kOuterType);
	initOre(outerRockArr);
	return true;
}

void Earth::initOre(Vector<Checkpoint::RockData *> rockArr, int tag){
	for(Checkpoint::RockData *rock : rockArr){
		 Ore* item = new Ore(rock->imageName, rock->positionX, rock->positionY,
				 rock->rotation, rock->score, rock->weight);
		item->setOpacity(0);
		item->setTag(tag ++);
		layer4->addChild(item);
		itemArr.pushBack(item);
	}
}

void Earth::showOre(){
    for(Ore* item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}
}

void Earth::startTurn(){
    layer1->runAction(RepeatForever::create(RotateBy::create(5.0f,45)));
    layer2->runAction(RepeatForever::create(RotateBy::create(6.0f,45)));
    layer3->runAction(RepeatForever::create(RotateBy::create(7.0f,45)));
    layer4->runAction(RepeatForever::create(RotateBy::create(8.0f,45)));
    
    for(Ore* item : itemArr){
		item->changeToNormalBody();
	}
}


void Earth::stopTurn() {
    this->stopAllActions();
    
    for(Ore* item : itemArr){
		item->changeToPhysicsBody();
	}
}
