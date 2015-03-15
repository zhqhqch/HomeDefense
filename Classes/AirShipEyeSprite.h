//
//  AirShipEyeSprite.h
//  HomeDefense
//
//  Created by huqichao on 15-3-15.
//
//

#ifndef __HomeDefense__AirShipEyeSprite__
#define __HomeDefense__AirShipEyeSprite__


#include "cocos2d.h"

class AirShipEye : public cocos2d::Sprite {
public:
    AirShipEye(float x, float y);
    
    //眼睛看下面
    void lookDown();
    
    //设置眼睛看的角度
    void changeLook(float lookAngle);
    
private:
    cocos2d::Sprite * eyes;
    
    
    void replaceEye();
};


#endif /* defined(__HomeDefense__AirShipEyeSprite__) */
