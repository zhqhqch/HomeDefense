/*
 * EarthLayer.h
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#ifndef EARTHLAYER_H_
#define EARTHLAYER_H_


#include "cocos2d.h"
#include "OreSprite.h"

class Earth : public cocos2d::Layer {
public:
	Earth();

    void setPhyWorld(cocos2d::PhysicsWorld* world) {m_world=world;};
    
    //显示矿石
    void showOre();
    
    //地球开始旋转
    void startTurn();
    
    //地球停止旋转
    void stopTurn();
    
private:
    cocos2d::Vector<Ore *> itemArr;
    
    cocos2d::PhysicsWorld* m_world;
    
    cocos2d::Sprite * layer1;
    cocos2d::Sprite * layer2;
    cocos2d::Sprite * layer3;
    cocos2d::Sprite * layer4;
    
	bool init();
    
};


#endif /* EARTHLAYER_H_ */
