/*
 * EarthLayer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "EarthLayer.h"


USING_NS_CC;

Earth::Earth(float x, float y){

	startX = x;
	startY = y;
	init();
}

bool Earth::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite * sprite1 = Sprite::create("earth_1.png");
	sprite1->setAnchorPoint(Vec2(1, 0));
	sprite1->setPosition(startX, startY);
	this->addChild(sprite1);

	Sprite * sprite2 = Sprite::create("earth_2.png");
	sprite2->setAnchorPoint(Vec2(0, 0));
	sprite2->setPosition(startX, startY);
	this->addChild(sprite2);

	Sprite * sprite3 = Sprite::create("earth_3.png");
	sprite3->setAnchorPoint(Vec2(0, 1));
	sprite3->setPosition(startX, startY);
	this->addChild(sprite3);

	Sprite * sprite4 = Sprite::create("earth_4.png");
	sprite4->setAnchorPoint(Vec2(1, 1));
	sprite4->setPosition(startX, startY);
	this->addChild(sprite4);

	return true;
}

