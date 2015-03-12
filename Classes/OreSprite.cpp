/*
 * OreSprite.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: hqch
 */

#include "OreSprite.h"
#include "Vec2Util.h"
#include "Constants.h"

USING_NS_CC;

Ore::Ore(const std::string& fileName, float x, float y, float r, int s, int w) {
	startX = x;
	startY = y;
	score = s;
	weight = w;

	Sprite::initWithFile(fileName);
	setPosition(x,y);
	setRotation(r);

//	isFollow = false;
}


void Ore::changeToPhysicsBody() {
    auto body = PhysicsBody::createCircle(getContentSize().width / 2);
    body->setDynamic(true);
    body->setContactTestBitmask(0x0001);
    body->setCategoryBitmask(0x0001);
    body->setCollisionBitmask(0x0001);
    body->setGravityEnable(false);
    body->getFirstShape()->setRestitution(0);
    setPhysicsBody(body);
}

void Ore::changeToNormalBody() {
    setPhysicsBody(nullptr);
}

int Ore::getScore() {
    return score;
}


void Ore::startFollow(Magnetite * m, float rotation) {
	if(isFollow){
		return;
	}
	isFollow = true;

	Point mPoint = m->getPosition();

	float len = getContentSize().width / 2 + m->getContentSize().width / 2;
	Vec2 point = Vec2Util::getTargetPoint(m->getStartPoint(), len, rotation);
	MoveTo * moveTo = MoveTo::create(kMoveBackTime, point);
	this->runAction(moveTo);
}
