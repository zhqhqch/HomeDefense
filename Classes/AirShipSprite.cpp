/*
 * AirShipSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipSprite.h"
#include "AirShipRopeSprite.h"
#include "EllipseBy.h"

USING_NS_CC;

AirShip::AirShip(float x, float y){

	Sprite::initWithFile("airship_game.png");
	y = y + getContentSize().height;
	setPosition(x, y);
    
    isPause = false;
}

void AirShip::makeCurPosition() {
    Point p = getPosition();
    startX = p.x;
    startY = p.y;
}

void AirShip::startMove() {

    if (isPause) {
        this->resume();
    } else {
        //椭圆旋转
//        EllipseConfig config;
//        config.ellipseA = 5;
//        config.ellipseB = 15;
//        config.cenPos = Vec2(startX, startY);
//        config.isAntiClockwise = true;
//        config.startAngle = 0;
//        config.selfAngle = 45;
//        this->runAction(RepeatForever::create(EllipseBy::create(2.5f,config)));

        MoveTo *moveTo = MoveTo::create(2.0f, Vec2(startX, startY + 30));
        MoveTo *moveBack = MoveTo::create(2.0f, Vec2(startX, startY));
		Sequence *seq = Sequence::create(moveTo,moveBack,NULL);
		this->runAction(RepeatForever::create(seq));
    }
}

void AirShip::stopMove() {
    this->pause();
    isPause = true;
}
