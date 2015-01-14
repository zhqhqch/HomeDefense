/*
 * AirShipSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPSPRITE_H_
#define AIRSHIPSPRITE_H_


#include "cocos2d.h"
#include "AirShipRopeSprite.h"

class AirShip : public cocos2d::Sprite {

public:
	AirShip(float x, float y);

private:
	AirShipRope * ropeSprite;
    float startX;
    float startY;
};

#endif /* AIRSHIPSPRITE_H_ */
