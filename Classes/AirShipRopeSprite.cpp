/*
 * AirShipRopeSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipRopeSprite.h"
#include "Vec2Util.h"
#include "Constants.h"
#include "GameViewScene.h"

USING_NS_CC;

const float move_step = 3.0f;
const float move_step_time = 0.05f;
const float init_rope_len = 50.0f;

#define NULLRef(type) (*((type*)(NULL)))

AirShipRope::AirShipRope(GameView * gw, float x, float y,float ca, bool isReal) {

    gameView = gw;
    startX = x;
    startY = y;
    catchAngle = ca;
    
	Sprite::initWithFile("line.png");
	setPosition(x, y);
    setAnchorPoint(Vec2(0.5f,1.0f));

	Size ropeSize = getContentSize();

	if(isReal){
		setTextureRect(Rect(0, 0, ropeSize.width, 0));
	}

	targetPoint = Sprite::create("target_point.png");
	this->addChild(targetPoint, 2);

//	targetOre = new Ore("item_a_3.png", ropeSize.width / 2, targetPoint->getContentSize().height,0,0);
//	targetOre->setVisible(false);
//    this->addChild(targetOre, 1);
    
    
    targetPointVelocity = Vec2(0, -20);
    
    isCatch = false;
}

void AirShipRope::reachProbe() {

//    Vector<FiniteTimeAction *> listAction;
    moving = true;
//    targetPoint->getPhysicsBody()->setVelocity(targetPointVelocity);
    
//	for(int i = 0;i<init_rope_len / move_step;i++){
//		DelayTime * dTime = DelayTime::create(move_step_time);
//		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::stretchRope, this, Vec2(0, move_step)));
//
//        listAction.pushBack(dTime);
//        listAction.pushBack(fun);
//	}
//
//    DelayTime * endTime = DelayTime::create(2.5f);
//    Point target = Point(targetPoint->getPosition().x, -50);
//    MoveTo * moveTo = MoveTo::create(2.0f, target);
//    listAction.pushBack(endTime);
//    CallFunc * endFun = CallFunc::create(CC_CALLBACK_0(AirShipRope::sawy, this));
//    listAction.pushBack(endFun);
//
//    Sequence *seq = Sequence::create(moveTo, endFun, NULL);
//    targetPoint->runAction(seq);

}

void AirShipRope::refreshRopeLen(Point targetPoint) {
    Vec2 start = Vec2(startX, startY);
    float len = targetPoint.distance(start);
    setTextureRect(Rect(0, 0, getTextureRect().size.width, len));
}

void AirShipRope::shrinkRope(Vec2 sub){
	Vec2 curRope = Vec2(getTextureRect().size.width, getTextureRect().size.height);
	Vec2 newRope = Vec2Util::subtract(curRope, sub);
	setTextureRect(Rect(0, 0, newRope.x, newRope.y));
    
    if(isCatch){
//    	Point curPoint = convertToWorldSpace(targetPoint->getPosition());
//    	targetOre->setPosition(curPoint.x, curPoint.y);
    }
}

void AirShipRope::sway() {
    if(isCatch){
        gameView->catchBack(targetOre);
    }
    
    
    isCatch = false;
	moving = false;
    ActionInterval *action1 = RotateTo::create(2,-90.0);
    ActionInterval *action2 = RotateTo::create(2, 90.0);
    float rotate = this->getRotation();
    Sequence *action3;
    if(rotate > 0){
        action3 = Sequence::create(action1,action2,NULL);
    } else {
        action3 = Sequence::create(action2,action1,NULL);
    }
    RepeatForever *repeat = RepeatForever::create(action3);
    this->runAction(repeat);
}


void AirShipRope::catchRock(Vec2 point){
	moving = true;
    this->stopAllActions();

//    Vec2 start = Vec2(startX, startY);
//    float distance = point.distance(start);
//
    Vector<FiniteTimeAction *> listAction;
//
//    int count = distance / move_step;
//
//    
//    targetPoint->getPhysicsBody()->setVelocity(targetPointVelocity);
//    targetPoint->getPhysicsBody()->setRotationOffset(getRotation());
//    
//	for(int i = 0;i<count;i++){
//		DelayTime * dTime = DelayTime::create(move_step_time);
//		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::stretchRope, this, Vec2(0, move_step)));
//
//		listAction.pushBack(dTime);
//		listAction.pushBack(fun);
//	}

//	DelayTime * endTime = DelayTime::create(0.5f);
//  listAction.pushBack(endTime);
    MoveTo *moveTo = MoveTo::create(3.0f, point);
	listAction.pushBack(moveTo);
	CallFunc * endFun = CallFunc::create(CC_CALLBACK_0(AirShipRope::hookBack, this,point, nullptr));
	listAction.pushBack(endFun);

	Sequence *seq = Sequence::create(listAction);
	this->runAction(seq);
}

void AirShipRope::hookBack(Vec2 point, Ore * catchOre) {
    this->stopAllActions();
    if(catchOre != nullptr){
		isCatch = true;
		targetOre = catchOre;
	}

    Vec2 start = Vec2(startX, startY);
    float distance = point.distance(start);

    Vector<FiniteTimeAction *> listAction;

	int count = distance / move_step;
	
	for(int i = 0;i<count;i++){
		DelayTime * dTime = DelayTime::create(move_step_time);
		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::shrinkRope, this, Vec2(0, move_step)));

		listAction.pushBack(dTime);
		listAction.pushBack(fun);
	}

	DelayTime * endTime = DelayTime::create(0.5f);
	listAction.pushBack(endTime);
	CallFunc * endFun = CallFunc::create(CC_CALLBACK_0(AirShipRope::sway, this));
	listAction.pushBack(endFun);

	Sequence *seq = Sequence::create(listAction);
	this->runAction(seq);
}


Point AirShipRope::grab(){
	if(moving){
		return kPintNull;
	}
    CCLOG("%f=====%f", getRotation(), catchAngle);

    Vec2 target;
    float rotation = getRotation();

    if(rotation > 0){
        if(rotation <= catchAngle){
        	target = getTargetPoint(rotation,true);
            target = getIntersectPoint(target, false, true);
        }else{
            target = getTargetPoint(rotation,true);
            target = getIntersectPoint(target, true, true);
        }
    }else if(rotation < 0){
        if(rotation <= -catchAngle){
            target = getTargetPoint(rotation,false);
            target = getIntersectPoint(target, true, false);
        }else{
            target = getTargetPoint(rotation,false);
            target = getIntersectPoint(target, false, false);
        }
    }else if(rotation == 0){
    	Size visibleSize = Director::getInstance()->getVisibleSize();
        target = Vec2(visibleSize.height, 0);
    }

    return Point(target.x, target.y);
}

Vec2 AirShipRope::getIntersectPoint(Vec2 start, bool isVertical, bool threeQuadrant) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 start1 = Vec2(startX, startY);
	Vec2 end1 = Vec2(0,0);
	Vec2 end2 = Vec2(0,0);
	if (threeQuadrant) {
		if(isVertical){
            end1 = Vec2(0,visibleSize.height);
			end2 = Vec2(0,0);
		} else {
            end1 = Vec2(0, 0);
			end2 = Vec2(visibleSize.width,0);
		}
	} else {
		if(isVertical){
			end1 = Vec2(visibleSize.width,0);
			end2 = Vec2(visibleSize.width, visibleSize.height);
		} else {
			end1 = Vec2(0, 0);
			end2 = Vec2(visibleSize.width, 0);
		}
	}

    return Vec2Util::getIntersectPoint(start1, start, end1, end2);
}

Vec2 AirShipRope::getTargetPoint(float rotation,bool threeQuadrant){

    if(threeQuadrant){
        rotation = 270 - rotation;
    } else {
        rotation = -(90 + rotation);
    }
    
    
    float radian = rotation * M_PI / 180;
    float xMargin = cos(radian) * 1;
    float yMargin = sin(radian) * 1;
    Vec2 target = Vec2(startX + xMargin,startY + yMargin);

	return target;
}
