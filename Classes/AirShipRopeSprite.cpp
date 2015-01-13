/*
 * AirShipRopeSprite.cpp
 *
 *  Created on: 2015年1月13日
 *      Author: hqch
 */

#include "AirShipRopeSprite.h"
#include "Vec2Util.h"

USING_NS_CC;

AirShipRope::AirShipRope(float x, float y) {

	Sprite::initWithFile("line.png");
	setPosition(x, y);
    setAnchorPoint(Vec2(0.5f,1.0f));

	Size ropeSize = getContentSize();

	setTextureRect(Rect(0, 0, ropeSize.width, 0));

	targetPoint = Sprite::create("target_point.png");
	targetPoint->setPosition(ropeSize.width / 2, 0);
//	targetPoint->setAnchorPoint(Vec2(0.5, 0));
//	targetPoint->setOpacity(0);
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
