/*
 * OreSptite.h
 *
 *  Created on: 2015年1月15日
 *      Author: hqch
 */

#ifndef ORESPTITE_H_
#define ORESPTITE_H_


#include "cocos2d.h"

class Ore : public cocos2d::Sprite {
public:
	Ore(const std::string& fileName, float x, float y, int score, int weight);
    int getScore();
    
private:
	float startX;
	float startY;
	int weight;
    int score;
};

#endif /* ORESPTITE_H_ */
