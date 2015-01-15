/*
 * AirShipLineSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPROPESPRITE_H_
#define AIRSHIPROPESPRITE_H_


#include "cocos2d.h"
#include "OreSprite.h"
class GameView;

class AirShipRope : public cocos2d::Sprite {

public:
	AirShipRope(GameView * gameView, float x, float y,float catchAngle);

	void reachProbe();
    
    cocos2d::Point grab();

    void hookBack(cocos2d::Point point, Ore * catchOre);

    void catchRock(cocos2d::Point point, Ore * ore);
private:
	cocos2d::Sprite * targetPoint;

	Ore * targetOre;
    GameView * gameView;

	void stretchRope(cocos2d::Vec2 add);
	void shrinkRope(cocos2d::Vec2 subtract);

    float useTime;
    bool moving;
    float catchAngle;
    float startX;
    float startY;
    bool isCatch;
    
    void sawy();
    void move();
    cocos2d::Vec2 getTargetPoint(float rotation,bool threeQuadrant);

    cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 start, bool isVertical, bool threeQuadrant);

};

#endif /* AIRSHIPROPESPRITE_H_ */
