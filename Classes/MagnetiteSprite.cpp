//
//  MagnetiteSprite.cpp
//  HomeDefense
//
//  Created by huqichao on 15-1-16.
//
//

#include "MagnetiteSprite.h"
#include "GameViewScene.h"

USING_NS_CC;

Magnetite::Magnetite(GameView *gw, float x, float y){
    startX = x;
    startY = y;
    gameView = gw;
    
    Sprite::initWithFile("target_point.png");
	setPosition(x, y);
    auto body = PhysicsBody::createCircle(getContentSize().width / 2);
	body->setDynamic(true);
	body->setContactTestBitmask(0x0001);
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	body->setGravityEnable(false);
	setPhysicsBody(body);
}


void Magnetite::reach() {
    move = true;
    Point target = Point(getPosition().x, getPosition().y - 40);
    MoveTo * moveTo = MoveTo::create(2.0f, target);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::finishMove, this));
    Sequence * seq = Sequence::create(moveTo, fun, NULL);
    
    this->runAction(seq);
}


void Magnetite::finishMove() {
    move = false;
    DelayTime * sleepTime = DelayTime::create(0.5f);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::readySway, this));
    Sequence * seq = Sequence::create(sleepTime, fun, NULL);
    this->runAction(seq);
}


void Magnetite::readySway() {
    gameView->startSway();
}