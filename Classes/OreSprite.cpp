/*
 * OreSprite.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: hqch
 */

#include "OreSprite.h"

USING_NS_CC;

Ore::Ore(const std::string& fileName, float x, float y, int s, int w) {
	startX = x;
	startY = y;
	score = s;
	weight = w;

	Sprite::initWithFile(fileName);
	setPosition(x,y);

	auto body = PhysicsBody::createCircle(getContentSize().width / 2);
	body->setDynamic(true);
	body->setContactTestBitmask(0x0001);
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	body->setGravityEnable(false);
	setPhysicsBody(body);
}

int Ore::getScore() {
    return score;
}
