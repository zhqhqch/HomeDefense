/*
 * OreSprite.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: hqch
 */

#include "OreSprite.h"

USING_NS_CC;

Ore::Ore(const std::string& fileName, float x, float y, int s, int w) {
	startX = x;
	startY = y;
	score = s;
	weight = w;

	Sprite::initWithFile(fileName);
	setPosition(x,y);
}


int Ore::getScore() {
    return score;
}
