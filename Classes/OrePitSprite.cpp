/*
 * OrePitSprite.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: hqch
 */


#include "OrePitSprite.h"
#include "AnimationUtil.h"
#include "Constants.h"

USING_NS_CC;

OrePit::OrePit(const std::string& fileName, float x, float y, float r) {
	Sprite::initWithSpriteFrameName(fileName);
	setPosition(x,y);
	setRotation(r);
}

void OrePit::playAnimation() {
    Sprite * layer = Sprite::create();
    Size size = getContentSize();
    layer->setPosition(size.width / 2, size.height / 2);
    this->addChild(layer);
    
    DelayTime * dt = DelayTime::create(0.5f);
    Animation * animation = AnimationUtil::getAnimationByName(Value(pitFallenRockAnimationName));
    animation->setDelayPerUnit(1.0f / pitFallenRockAnimationCount);
    animation->setRestoreOriginalFrame(true);
    Animate * action = Animate::create(animation);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(OrePit::removeAnimationBg, this, layer));
    Sequence * seq = Sequence::create(dt, action,fun, NULL);
    
    layer->runAction(seq);
}

void OrePit::removeAnimationBg(Sprite * layer) {
    layer->removeFromParentAndCleanup(true);
}
