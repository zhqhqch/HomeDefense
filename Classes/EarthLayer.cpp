/*
 * EarthLayer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "EarthLayer.h"


USING_NS_CC;


Earth::Earth(){
	init();
}

bool Earth::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

	Sprite * sprite1 = Sprite::create("earth_1.png");
	sprite1->setAnchorPoint(Vec2(1, 0));
	sprite1->setPosition(w, h);
	this->addChild(sprite1, 1);

	Sprite * sprite2 = Sprite::create("earth_2.png");
	sprite2->setAnchorPoint(Vec2(0, 0));
	sprite2->setPosition(w, h);
	this->addChild(sprite2, 1);

	Sprite * sprite3 = Sprite::create("earth_3.png");
	sprite3->setAnchorPoint(Vec2(0, 1));
	sprite3->setPosition(w, h);
	this->addChild(sprite3, 1);

	Sprite * sprite4 = Sprite::create("earth_4.png");
	sprite4->setAnchorPoint(Vec2(1, 1));
	sprite4->setPosition(w, h);
	this->addChild(sprite4, 1);
    
    
//    Sprite * ore1 = Sprite::create("item_a_1.png");
//	ore1->setPosition(100, 150);
//	this->addChild(ore1, 2);
    
    Ore* itemA1 = new Ore("item_a_1.png", 100, 150, 20, 3);
	itemA1->setOpacity(0);
	itemA1->setTag(10);
	this->addChild(itemA1, 2);
	itemArr.pushBack(itemA1);
    
	Ore* itemA2 = new Ore("item_a_2.png", 400, 80, 30, 4);
	itemA2->setOpacity(0);
	itemA2->setTag(11);
	this->addChild(itemA2, 1);
	itemArr.pushBack(itemA2);
    
	Ore* itemA3 = new Ore("item_a_3.png", 500, 140, 50, 5);
	itemA3->setOpacity(0);
	itemA3->setTag(12);
	this->addChild(itemA3, 1);
	itemArr.pushBack(itemA3);
    
    
	Ore* itemB1 = new Ore("item_b_1.png", 300, 50, 30, 4);
	itemB1->setOpacity(0);
	itemB1->setTag(13);
	this->addChild(itemB1, 1);
	itemArr.pushBack(itemB1);
    
	Ore* itemB2 = new Ore("item_b_2.png", 300, 180, 40, 5);
	itemB2->setOpacity(0);
	itemB2->setTag(14);
	this->addChild(itemB2, 1);
	itemArr.pushBack(itemB2);
    
	Ore* itemB3 = new Ore("item_b_3.png", 720, 200, 50, 6);
	itemB3->setOpacity(0);
	itemB3->setTag(15);
	this->addChild(itemB3, 1);
	itemArr.pushBack(itemB3);
    
	Ore* itemC1 = new Ore("item_c_1.png", 1100, 10, 20, 3);
	itemC1->setOpacity(0);
	itemC1->setTag(16);
	this->addChild(itemC1, 1);
	itemArr.pushBack(itemC1);
    
	Ore* itemC2 = new Ore("item_c_2.png", 970, 180, 30, 4);
	itemC2->setOpacity(0);
	itemC2->setTag(17);
	this->addChild(itemC2, 1);
	itemArr.pushBack(itemC2);
    
	Ore* itemC3 = new Ore("item_c_3.png", 900, 140, 40, 5);
	itemC3->setOpacity(0);
	itemC3->setTag(18);
	this->addChild(itemC3, 1);
	itemArr.pushBack(itemC3);

	return true;
}


void Earth::showOre(){
    for(Ore* item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}
}

void Earth::startTurn(){
    this->runAction(RepeatForever::create(RotateBy::create(5.0f,45)));
    
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
