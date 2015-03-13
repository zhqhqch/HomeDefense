/*
 * OrePitSprite.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: hqch
 */


#include "OrePitSprite.h"

OrePit::OrePit(const std::string& fileName, float x, float y, float r) {
	Sprite::initWithSpriteFrameName(fileName);
	setPosition(x,y);
	setRotation(r);
}

void OrePit::playAnimation() {

}
