/*
 * GameViewScene.h
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#ifndef GAMEVIEWSCENE_H_
#define GAMEVIEWSCENE_H_

#include "cocos2d.h"
#include "AirShipSprite.h"
#include "EarthLayer.h"
#include "OreSprite.h"
#include "MagnetiteSprite.h"
#include "OreSprite.h"
#include "AirShipRopeSprite.h"

class Checkpoint;

class GameView : public cocos2d::Scene {
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameView);

private:
	cocos2d::PhysicsWorld* m_world;
	AirShip *airshipSprite;
	Earth *earthLayer;
    bool shipMove;
    cocos2d::Sprite *trackPointSprite;
    cocos2d::Sprite *trackSprite;
    Magnetite *magnetite;
    bool isCatch;
    Ore *targetOre;
    AirShipRope *airShipRopeSprite;
    bool isReady;
    bool isPause;
    
    Checkpoint *checkpoint;
    


	void setPhyWorld(cocos2d::PhysicsWorld* world) {m_world=world;};

	//过场动画结束后调用
	virtual void onEnterTransitionDidFinish();
	//刷新界面
	void update(float dTime);
	//触发碰撞时调用
	bool onContactBegin(const cocos2d::PhysicsContact& contact);
	//屏幕触屏事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	//返回按钮事件
	void menuBackCallback(cocos2d::Ref* pSender);

    //开始游戏
    void startGame();
    
    //使用道具
    void useProp(int propID);
    
    //暂停或继续游戏
    void pauseGame();
};


#endif /* GAMEVIEWSCENE_H_ */
