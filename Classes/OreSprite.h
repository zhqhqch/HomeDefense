/*
 * OreSptite.h
 *
 *  Created on: 2015年1月15日
 *      Author: hqch
 */

#ifndef ORESPTITE_H_
#define ORESPTITE_H_


#include "cocos2d.h"
#include "MagnetiteSprite.h"

class Ore : public cocos2d::Sprite {
public:
	Ore(const std::string& fileName, float x, float y, float r, int s, int w);
    
    void startFollow(Magnetite * m, float rotation);
    
    void changeToPhysicsBody();
    void changeToNormalBody();

    std::string getImageName(){return imageName;}
    float getPositionX(){return startX;}
    float getPositionY(){return startY;}
    int getScore(){return score;}
    int getWeight(){return weight;}
private:
    std::string imageName;
	float startX;
	float startY;
	int weight;
    int score;
    bool isFollow;
};

#endif /* ORESPTITE_H_ */
