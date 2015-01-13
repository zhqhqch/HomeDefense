/*
 * AirShipLineSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPROPESPRITE_H_
#define AIRSHIPROPESPRITE_H_


#include "cocos2d.h"

class AirShipRope : public cocos2d::Sprite {

public:
	AirShipRope(float x, float y);

	void reachProbe();
    
    void sawy();
    
private:
	cocos2d::Sprite * targetPoint;

	void stretchRope(cocos2d::Vec2 add);
};

#endif /* AIRSHIPROPESPRITE_H_ */
