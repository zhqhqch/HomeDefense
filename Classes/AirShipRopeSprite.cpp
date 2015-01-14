/*
 * AirShipRopeSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipRopeSprite.h"
#include "Vec2Util.h"

USING_NS_CC;

AirShipRope::AirShipRope(float x, float y,float ca) {

    startX = 0;
    startY = 0;
    getTargetPoint(225,true);
    
    
    startX = x;
    startY = y;
    catchAngle = ca;
    
	Sprite::initWithFile("line.png");
	setPosition(x, y);
    setAnchorPoint(Vec2(0.5f,1.0f));
//    setScaleY(0.1f);

	Size ropeSize = getContentSize();

	setTextureRect(Rect(0, 0, ropeSize.width, 0));

	targetPoint = Sprite::create("target_point.png");
	targetPoint->setPosition(ropeSize.width / 2, 0);
//	targetPoint->setAnchorPoint(Vec2(0.5, 0));
//	targetPoint->setOpacity(0);
//	targetPoint->setScaleY(1.0f);
	this->addChild(targetPoint);
}

void AirShipRope::reachProbe() {

    Vector<FiniteTimeAction *> listAction;

	for(int i = 0;i<10;i++){
		DelayTime * dTime = DelayTime::create(0.1f);
		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::stretchRope, this, Vec2(0, 5)));

        listAction.pushBack(dTime);
        listAction.pushBack(fun);
	}

    DelayTime * endTime = DelayTime::create(0.5f);
    listAction.pushBack(endTime);
    CallFunc * endFun = CallFunc::create(CC_CALLBACK_0(AirShipRope::sawy, this));
    listAction.pushBack(endFun);

    Sequence *seq = Sequence::create(listAction);
    this->runAction(seq);

}


void AirShipRope::stretchRope(Vec2 add){
	Vec2 curRope = Vec2(getTextureRect().size.width, getTextureRect().size.height);
	Vec2 newRope = Vec2Util::add(curRope, add);
    setTextureRect(Rect(0, 0, newRope.x, newRope.y));
}

void AirShipRope::sawy() {
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
    this->stopAllActions();

    //    setAnchorPoint(Vec2(0.5, 0));

    Vec2 start = Vec2(startX, startY);
    float distance = point.distance(start);
    useTime = distance * 0.01;

    ActionInterval *actionTo = MoveTo::create(useTime, point);
    //    ActionInterval *actionTo = MoveBy::create(useTime, Vec2(10, 10));
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::hookBack, this, false));
    Sequence *seq = Sequence::create(actionTo,fun,NULL);
    this->runAction(seq);
}

void AirShipRope::hookBack(bool isCatch) {

    this->stopAllActions();

    Size winSize = Director::getInstance()->getWinSize();
    ActionInterval *action4 = MoveTo::create(useTime, Vec2(startX, startY));
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(AirShipRope::sawy, this));
    Sequence *seq = Sequence::create(action4,func,NULL);
    this->runAction(seq);
}


void AirShipRope::grab(){
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

    CCLOG("########%f#######%f",target.x, target.y);

    moving = true;

    catchRock(Vec2(target.x, target.y));
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

	CCLog("target==========%f======%f$$$$$%f^^^^^%f", target.x, target.y,startX,startY);
	return target;
}
