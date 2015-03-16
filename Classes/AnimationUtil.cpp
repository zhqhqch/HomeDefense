//
//  AnimationUtil.cpp
//  HomeDefense
//
//  Created by huqichao on 15-3-14.
//
//

#include "AnimationUtil.h"
#include "AirShipSprite.h"


USING_NS_CC;

void AnimationUtil::createAnimationByName(Value animationName, Value prefixStr, int count) {
    auto animation = Animation::create();
    SpriteFrameCache * cache = SpriteFrameCache::getInstance();
    for( int i = 0;i < count;i++) {
        char szName[20] = {0};
        sprintf(szName, "-%05d.png", i);
        SpriteFrame* frame = cache->getSpriteFrameByName(prefixStr.asString() + szName);
        animation->addSpriteFrame(frame);
    }

    AnimationCache::getInstance()->addAnimation(animation, animationName.asString());
}


Animation * AnimationUtil::getAnimationByName(Value animationName) {
    return AnimationCache::getInstance()->getAnimation(animationName.asString());
}