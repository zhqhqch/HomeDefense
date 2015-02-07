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
class GameViewOld;

class AirShipRope : public cocos2d::Sprite {

public:
	AirShipRope(GameViewOld * gw, float x, float y,float catchAngle);
    
	//获取绳子延伸方向上，在屏幕边缘上的点
    cocos2d::Point grab();

    //刷新绳子的长度
    void refreshRopeLen(cocos2d::Point targetPoint, bool isReach, bool isBack);
    //绳子左右摇摆
    void sway();
    
    //获取绳子的终点
    cocos2d::Point getRopeEndPoint();
    
    cocos2d::Point getRopeStartPoint(){return cocos2d::Point(startX, startY);}

    //判断绳子是否在摇摆
    bool isSway(){return _sway;}
private:
	cocos2d::Sprite * targetPoint;

    bool moving;
    float catchAngle;
    float startX;
    float startY;
    bool _sway;
    float roepLen;
    
    GameViewOld *gameView;

    cocos2d::Vec2 getTargetPoint(float rotation);

};

#endif /* AIRSHIPROPESPRITE_H_ */
