/*
 * AirShipLineSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPROPESPRITE_H_
#define AIRSHIPROPESPRITE_H_


#include "cocos2d.h"
#include "OreSptite.h"

class AirShipRope : public cocos2d::Sprite {

public:
	AirShipRope(float x, float y,float catchAngle);

	void reachProbe();
    
    void sawy();
    
    cocos2d::Point grab();

    void hookBack(bool isCatch, cocos2d::Point point);

    void catchRock(cocos2d::Point point, Ore * ore);
private:
	cocos2d::Sprite * targetPoint;

	Ore * targetOre;

	void stretchRope(cocos2d::Vec2 add);
	void shrinkRope(cocos2d::Vec2 subtract);

    float useTime;
    bool moving;
    float catchAngle;
    float startX;
    float startY;
    
    void move();
    cocos2d::Vec2 getTargetPoint(float rotation,bool threeQuadrant);

    cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 start, bool isVertical, bool threeQuadrant);

};

#endif /* AIRSHIPROPESPRITE_H_ */
