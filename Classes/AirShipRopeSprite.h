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
#include "MagnetiteSprite.h"
class GameView;

class AirShipRope : public cocos2d::Sprite {

public:
	AirShipRope(GameView * gameView, Magnetite * magnetite,float x, float y,float catchAngle, bool isReal);

	void reachProbe();
    
    cocos2d::Point grab();

    void hookBack(cocos2d::Point point, Ore * catchOre);

    void catchRock(cocos2d::Point point);
    //刷新绳子的长度
    void refreshRopeLen(cocos2d::Point targetPoint);
    //绳子左右摇摆
    void sway();
private:
//	cocos2d::Sprite * targetPoint;

	Ore * targetOre;
    Magnetite * magnetite;
    GameView * gameView;

	void stretchRope(cocos2d::Vec2 add);
	void shrinkRope(cocos2d::Vec2 subtract);

    float useTime;
    bool moving;
    float catchAngle;
    float startX;
    float startY;
    bool isCatch;
    cocos2d::Vec2 targetPointVelocity;
    
    void move();
    cocos2d::Vec2 getTargetPoint(float rotation,bool threeQuadrant);

    cocos2d::Vec2 getIntersectPoint(cocos2d::Vec2 start, bool isVertical, bool threeQuadrant);

};

#endif /* AIRSHIPROPESPRITE_H_ */
