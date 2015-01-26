//
//  MagnetiteSprite.cpp
//  HomeDefense
//
//  Created by huqichao on 15-1-16.
//
//

#include "MagnetiteSprite.h"
#include "GameViewScene.h"
#include "AirShipRopeSprite.h"
#include "Constants.h"

USING_NS_CC;

Magnetite::Magnetite(GameView *gw, float x, float y){
    gameView = gw;
    
    Sprite::initWithFile("target_point.png");
	setPosition(x, y);
    auto body = PhysicsBody::createCircle(getContentSize().width / 2);
	body->setDynamic(true);
	body->setContactTestBitmask(0x0001);
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	body->setGravityEnable(false);
	body->getFirstShape()->setRestitution(0.5f);
	setPhysicsBody(body);

	showScore = false;
}


//将磁铁石伸出飞船
void Magnetite::reach() {
    move = true;
    reachRope = true;
    backRope = false;
    Point target = Point(getPosition().x, getPosition().y - 50);
    MoveTo * moveTo = MoveTo::create(2.0f, target);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::finishMove, this, kMagnetiteFinishMove_Sway));
    Sequence * seq = Sequence::create(moveTo, fun, NULL);
    
    this->runAction(seq);
}


void Magnetite::finishMove(int nextActionType) {
	reachRope = false;
    if(nextActionType == kMagnetiteFinishMove_Sway){
    	DelayTime * sleepTime = DelayTime::create(0.5f);
		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::readySway, this));
		Sequence * seq = Sequence::create(sleepTime, fun, NULL);
		this->runAction(seq);
    } else if(nextActionType == kMagnetiteFinishMove_Back){
    	DelayTime * sleepTime = DelayTime::create(0.2f);
		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::backToStartPoint, this));
		Sequence * seq = Sequence::create(sleepTime, fun, NULL);
		this->runAction(seq);
    }
}


void Magnetite::readySway() {
	move = false;
	reachRope = false;
    log("$$$$$$$$$$$$$$$$");
    gameView->startSway();
    if(showScore){
    	gameView->catchBack();
    }
}

void Magnetite::startFollow(Point point) {
    setPosition(point);
}

void Magnetite::stopMove(){
	getPhysicsBody()->setVelocity(Vec2::ZERO);
	readySway();
}

void Magnetite::moveToPoint(Point curPoint, Point targetPoint) {
	move = true;
	startPoint = curPoint;
	showScore = false;
	backRope = false;

	log("start^^^^^%f===%f", startPoint.x, startPoint.y);

//	MoveTo * moveTo = MoveTo::create(5.0f, targetPoint);
//	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::finishMove, this, kMagnetiteFinishMove_Back));
//	Sequence * seq = Sequence::create(moveTo, fun, NULL);
//	this->runAction(seq);

	Vec2 tmp = Vec2(targetPoint.x, targetPoint.y);
	tmp.subtract(getPosition());
	tmp.normalize();
	moveVelocity = tmp.operator *=(200);
	getPhysicsBody()->setVelocity(moveVelocity);
}

void Magnetite::backToStartPoint(){
	move = true;
	backRope = true;

//  this->stopAllActions();
//	MoveTo * moveTo = MoveTo::create(kMoveBackTime, startPoint);
//	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::finishMove, this, kMagnetiteFinishMove_Sway));
//	Sequence * seq = Sequence::create(moveTo, fun, NULL);
//	this->runAction(seq);

	moveVelocity.negate();
	getPhysicsBody()->setVelocity(moveVelocity);
}

void Magnetite::backWithOreToStartPoint(){
	move = true;
	showScore = true;
	backRope = true;
	log("end^^^^^%f===%f", startPoint.x, startPoint.y);

//	this->stopAllActions();
//	MoveTo * moveTo = MoveTo::create(kMoveBackTime, startPoint);
//	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Magnetite::finishMove, this, kMagnetiteFinishMove_Sway));
//	Sequence * seq = Sequence::create(moveTo, fun, NULL);
//	this->runAction(seq);

	moveVelocity.negate();
	moveVelocity = moveVelocity.operator /(10);
	getPhysicsBody()->setVelocity(moveVelocity);
}
