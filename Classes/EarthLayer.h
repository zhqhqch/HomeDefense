/*
 * EarthLayer.h
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#ifndef EARTHLAYER_H_
#define EARTHLAYER_H_


#include "cocos2d.h"

class Earth : public cocos2d::Layer {
public:
	Earth(float x, float y);

private:
	float startX, startY;

	bool init();
};


#endif /* EARTHLAYER_H_ */
