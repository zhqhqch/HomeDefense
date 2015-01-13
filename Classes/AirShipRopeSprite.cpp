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

	Size ropeSize = getContentSize();

	setTextureRect(Rect(0, 0, ropeSize.width, 0));

	targetPoint = Sprite::create("target_point.png");
	targetPoint->setPosition(ropeSize.width / 2, 0);
	targetPoint->setAnchorPoint(Vec2(0.5, 0));
//	targetPoint->setOpacity(0);
	this->addChild(targetPoint);
}

void AirShipRope::reachProbe() {
//	Vec2 end = Vec2Util::addY(targetPoint->getPosition(), -40);
//	MoveBy * moveBy = MoveBy::create(1.5f, end);

//	float ropeLen = end.distance(getPosition());
//	setTextureRect(Rect(0, 0, getContentSize().width, ropeLen));

//	this->runAction(moveBy);

//	stretch(40);
	for(int i = 0;i<10;i++){
//		MoveBy * moveBy = MoveBy::create(1.0f, Vec2(0, -5));
//		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::stretchRope, this, Vec2(0, 5)));
//		ScaleBy * scaleBy = ScaleBy::create(1.0f, 1.0f, 1.2f);
//		this->runAction(scaleBy);

		DelayTime * dTime = DelayTime::create(0.5f);
		CallFunc *fun = CallFunc::create(CC_CALLBACK_0(AirShipRope::stretchRope, this, Vec2(0, 5)));
		Sequence *seq = Sequence::create(dTime, fun, NULL);
		this->runAction(seq);
//		targetPoint->runAction(moveBy);
	}

}


void AirShipRope::stretchRope(Vec2 add){
	Vec2 curRope = Vec2(getTextureRect().size.width, getTextureRect().size.height);
	Vec2 newRope = Vec2Util::add(curRope, add);

	CCLog("====%f===%f=====%f===%f=====%f=====%f", targetPoint->getPosition().x, targetPoint->getPosition().y, newRope.x, newRope.y, getContentSize().width,getContentSize().height);

	setTextureRect(Rect(0, 0, newRope.x, newRope.y));
}
