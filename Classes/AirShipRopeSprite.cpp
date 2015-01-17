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

AirShipRope::AirShipRope(float x, float y,float ca) {
    startX = x;
    startY = y;
    catchAngle = ca;
    
	Sprite::initWithFile("line.png");
	setPosition(x, y);
    setAnchorPoint(Vec2(0.5f,1.0f));

	Size ropeSize = getContentSize();

	setTextureRect(Rect(0, 0, ropeSize.width, 0));

	targetPoint = Sprite::create("item_c_2.png");
	targetPoint->setPosition(ropeSize.width / 2, 0);
//	targetPoint->setVisible(false);
	this->addChild(targetPoint, 2);
}

void AirShipRope::refreshRopeLen(Point targetPoint) {
	_sway = false;
	moving = true;
	this->stopAllActions();
    Vec2 start = Vec2(startX, startY);
    float len = targetPoint.distance(start);
    setTextureRect(Rect(0, 0, getTextureRect().size.width, len));
}


void AirShipRope::sway() {
	_sway = true;
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
