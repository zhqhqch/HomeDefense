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
	y = y + getContentSize().height;
	setPosition(x, y);
    
    startX = x;
    startY = y;
}
