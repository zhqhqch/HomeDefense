/*
 * AirShipSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPSPRITE_H_
#define AIRSHIPSPRITE_H_


#include "cocos2d.h"

class AirShipEye;
class AirShipRope;


class AirShip : public cocos2d::Sprite {

public:
	AirShip(float x, float y);
    //飞船开始飞
    void startMove();

    //飞船停止飞
    void stopMove();
    
    //当飞船出场后，记录当前位置
    void makeCurPosition();
    
    //设置飞船眼睛看下面
    void eyeLookDown();
    
    //设置飞船眼睛看的角度
    void eyeLook(float eyeLookAngle);

private:
	AirShipRope * ropeSprite;
    AirShipEye * eyeSprite;
    float startX;
    float startY;
    bool isPause;
    
};

#endif /* AIRSHIPSPRITE_H_ */
