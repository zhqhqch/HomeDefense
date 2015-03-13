/*
 * OrePitSprite.h
 *
 *  Created on: 2015年3月13日
 *      Author: hqch
 */

#ifndef OREPITSPRITE_H_
#define OREPITSPRITE_H_


#include "cocos2d.h"

class OrePit : public cocos2d::Sprite {
public:
	OrePit(const std::string& fileName, float x, float y, float r);

	//播放矿石从坑中抓走时的动画
	void playAnimation();
};


#endif /* OREPITSPRITE_H_ */
