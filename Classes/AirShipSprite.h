/*
 * AirShipSprite.h
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#ifndef AIRSHIPSPRITE_H_
#define AIRSHIPSPRITE_H_


#include "cocos2d.h"
#include "AirShipEyeSprite.h"

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
    
    //播放正在抓取的动画
    void playCatchAnimation();
    
    //播放抓取成功的动画
    void playCatchedSuccessAnimation();
    
    //播放抓取失败的动画
    void playCatchedFailAnimation();

private:
	AirShipRope * ropeSprite;
    AirShipEye * eyeSprite;
    float startX;
    float startY;
    
    //停止正在抓取的动画
    void stopCatchAnimation();
    
    //动画结束后显示眼睛
    void eyeBack();
};

#endif /* AIRSHIPSPRITE_H_ */
