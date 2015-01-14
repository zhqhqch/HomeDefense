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
	AirShipRope(float x, float y,float catchAngle);

	void reachProbe();
    
    void sawy();
    
    void grab();

    void hookBack(bool isCatch);

    void catchRock(cocos2d::Point point);

private:
	cocos2d::Sprite * targetPoint;

	void stretchRope(cocos2d::Vec2 add);

    float useTime;
    bool moving;
    float catchAngle;
    float startX;
    float startY;
    
    void move();
    cocos2d::Vec2 getTargetPoint(float rotation);

    cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 start, bool isVertical, bool threeQuadrant);

};

#endif /* AIRSHIPROPESPRITE_H_ */
