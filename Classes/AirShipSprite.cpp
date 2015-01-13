/*
 * AirShipSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipSprite.h"
#include "AirShipRopeSprite.h"

USING_NS_CC;

AirShip::AirShip(float x, float y){

	Sprite::initWithFile("airship_game.png");
	setPosition(x, y);
    
    startX = x;
    startY = y;
}

void AirShip::showRope(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float catchAngle = atan2(fabs(startX - visibleSize.width),fabs(startY-visibleSize.height));
    catchAngle = CC_RADIANS_TO_DEGREES(catchAngle);

    
	Size airshipSize = getContentSize();
	ropeSprite = new AirShipRope(airshipSize.width / 2, 0, catchAngle);
//	ropeSprite->setOpacity(0);
//	this->addChild(ropeSprite, -1); //隐藏绳子在飞船背后
	this->addChild(ropeSprite);

	ropeSprite->reachProbe();
    
//    ropeSprite->sawy();
}


void AirShip::grab() {
    ropeSprite->grab();
}
