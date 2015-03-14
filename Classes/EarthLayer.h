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
#include "OrePitSprite.h"
#include "Checkpoint.h"

class GameView;

class Earth : public cocos2d::Layer {
public:
	Earth(GameView * gw, Checkpoint *c);

    void setPhyWorld(cocos2d::PhysicsWorld* world) {m_world=world;};
    
    //显示矿石
    void showOre();
    
    //地球开始旋转
    void startTurn();
    
    //地球停止旋转
    void stopTurn();
    
    //检测是否抓取到矿石
    bool isCatchOre(cocos2d::Point point, float r);

private:
    cocos2d::Vector<Ore *> oreArr;
    cocos2d::Vector<OrePit *> orePitArr;
    cocos2d::PhysicsWorld* m_world;
    cocos2d::Sprite * layer1;
    cocos2d::Sprite * layer2;
    cocos2d::Sprite * layer3;
    cocos2d::Sprite * layer4;
    
    Checkpoint *checkpoint;
    GameView * gameView;

    bool isCatch;

	bool init();
    
	void initOre(cocos2d::Vector<Checkpoint::RockData *> rockArr, int tag);
};


#endif /* EARTHLAYER_H_ */
