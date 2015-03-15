//
//  AirShipEyeSprite.cpp
//  HomeDefense
//
//  Created by huqichao on 15-3-15.
//
//

#include "AirShipEyeSprite.h"

USING_NS_CC;

AirShipEye::AirShipEye(float x, float y){
    Sprite::initWithSpriteFrameName("player-eye.png");
	setPosition(x, y);
    
    eyes = Sprite::createWithSpriteFrameName("player-eyes.png");
    Size size = getContentSize();
    eyes->setPosition(size.width / 2, size.height / 2);
    this->addChild(eyes);
}

void AirShipEye::lookDown() {
    Size size = getContentSize();
    MoveTo * moveTo = MoveTo::create(0.5f, Vec2(size.width / 2, size.height / 2 - 7));
    eyes->runAction(moveTo);
}

void AirShipEye::changeLook(float lookAngle) {
    log("^^^^^^^^^^^^%f", lookAngle);
}