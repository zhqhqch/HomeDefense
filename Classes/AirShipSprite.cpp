/*
 * AirShipSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipSprite.h"
#include "AirShipRopeSprite.h"
#include "EllipseBy.h"
#include "AnimationUtil.h"
#include "Constants.h"


USING_NS_CC;

AirShip::AirShip(float x, float y){

	Sprite::initWithSpriteFrameName("player-normal.png");
    
    Size size = getContentSize();
    
	y = y + size.height;
	setPosition(x, y);
    
    eyeSprite = new AirShipEye(size.width / 2, size.height / 2);
    this->addChild(eyeSprite);
}

void AirShip::makeCurPosition() {
    Point p = getPosition();
    startX = p.x;
    startY = p.y;
}

void AirShip::startMove() {
        //椭圆旋转
//        EllipseConfig config;
//        config.ellipseA = 5;
//        config.ellipseB = 15;
//        config.cenPos = Vec2(startX, startY);
//        config.isAntiClockwise = true;
//        config.startAngle = 0;
//        config.selfAngle = 45;
//        this->runAction(RepeatForever::create(EllipseBy::create(2.5f,config)));
    
    stopCatchAnimation();
    
    MoveTo *moveTo = MoveTo::create(2.0f, Vec2(startX, startY + 30));
    MoveTo *moveBack = MoveTo::create(2.0f, Vec2(startX, startY));
    Sequence *seq = Sequence::create(moveTo,moveBack,NULL);
    RepeatForever * moveAction = RepeatForever::create(seq);
    moveAction->setTag(kAirShipMove);
    this->runAction(moveAction);
}

void AirShip::stopMove() {
    this->stopActionByTag(kAirShipMove);
}

void AirShip::eyeLookDown() {
    eyeSprite->lookDown();
}


void AirShip::eyeLook(float eyeLookAngle) {
    eyeSprite->changeLook(eyeLookAngle);
}

void AirShip::playCatchAnimation() {
    Animation * animation = AnimationUtil::getAnimationByName(Value(catchingAnimationName));
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);
    Animate * action = Animate::create(animation);

    RepeatForever * repeat = RepeatForever::create(action);
    repeat->setTag(kAirShipCatching);
    this->runAction(repeat);
}

void AirShip::stopCatchAnimation() {
    this->stopActionByTag(kAirShipCatching);
}

void AirShip::playCatchedSuccessAnimation() {
    eyeSprite->setVisible(false);
    
    Animation * animation = AnimationUtil::getAnimationByName(Value(catchedSuccessAnimationName));
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);
    Animate * action = Animate::create(animation);
    Repeat * repeat = Repeat::create(action, 3);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShip::eyeBack, this));
    Sequence * seq = Sequence::create(repeat, fun, NULL);
    this->runAction(seq);

}

void AirShip::playCatchedFailAnimation() {
    eyeSprite->setVisible(false);
    
    Animation * animation = AnimationUtil::getAnimationByName(Value(catchedFailAnimationName));
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);
    Animate * action = Animate::create(animation);
    Repeat * repeat = Repeat::create(action, 3);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShip::eyeBack, this));
    Sequence * seq = Sequence::create(repeat, fun, NULL);
    this->runAction(seq);
}

void AirShip::eyeBack() {
    eyeSprite->setVisible(true);
}