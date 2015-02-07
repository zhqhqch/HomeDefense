/*
 * AirShipRopeSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipRopeSprite.h"
#include "Vec2Util.h"
#include "Constants.h"
#include "GameViewOldScene.h"

USING_NS_CC;


AirShipRope::AirShipRope(GameViewOld * gw, float x, float y,float ca) {
    startX = x;
    startY = y;
    catchAngle = ca;
    gameView = gw;
    
	Sprite::initWithFile("line.png");
	setPosition(x, y);
    setAnchorPoint(Vec2(0.5f,1.0f));

	Size ropeSize = getContentSize();

	setTextureRect(Rect(0, 0, ropeSize.width, 0));

	targetPoint = Sprite::create("item_c_2.png");
	targetPoint->setPosition(ropeSize.width / 2, 0);
//    targetPoint->setAnchorPoint(Vec2(0.0f, 0.0f));
//	targetPoint->setVisible(false);
	this->addChild(targetPoint);
}

void AirShipRope::refreshRopeLen(Point point, bool isReach, bool isBack) {
	_sway = false;
	moving = true;
	this->stopAllActions();
    Vec2 start = Vec2(startX, startY);
    float len = point.distance(start);
    if(isReach){
    	roepLen = len;
    } else if(!isReach && isBack && len < roepLen){
    	setTextureRect(Rect(0, 0, getTextureRect().size.width, roepLen));
    	gameView->stopMagnetite();
    	return;
    }
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

Point AirShipRope::getRopeEndPoint(){

    Point retPoint = convertToWorldSpace(targetPoint->getPosition());

    return retPoint;
}

Point AirShipRope::grab(){
	if(moving){
		return kPintNull;
	}
    
    log("%f=====%f", getRotation(), catchAngle);
    
    float rotation = getRotation();
    Point target;

    if(rotation == 0){
    	Size visibleSize = Director::getInstance()->getVisibleSize();
        target = Vec2(visibleSize.width / 2, 0);
    } else {
        target = getTargetPoint(getRotation());
    }

    return target;
}

Vec2 AirShipRope::getTargetPoint(float rotation){
    float len = Director::getInstance()->getVisibleSize().width;

	return Vec2Util::getTargetPoint(Point(startX, startY), len, rotation);
}
