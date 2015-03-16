//
//  AnimationUtil.h
//  HomeDefense
//
//  Created by huqichao on 15-3-14.
//
//

#ifndef __HomeDefense__AnimationUtil__
#define __HomeDefense__AnimationUtil__


#include "cocos2d.h"

class AirShip;

class AnimationUtil {
public:
    static void createAnimationByName(cocos2d::Value animationName, cocos2d::Value prefixStr, int count);
    
    static cocos2d::Animation * getAnimationByName(cocos2d::Value animationName);

};

#endif /* defined(__HomeDefense__AnimationUtil__) */
