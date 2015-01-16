/*
 * GameViewScene.h
 *
 *  Created on: 2015年1月12日
 *      Author: hqch
 */

#ifndef __GAMEVIEW_SCENE_H__
#define __GAMEVIEW_SCENE_H__

#include "cocos2d.h"
#include "AirShipSprite.h"
#include "AirShipRopeSprite.h"
#include "OreSprite.h"
#include "MagnetiteSprite.h"

class GameView : public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameView);

	void setPhyWorld(cocos2d::PhysicsWorld* world) {m_world=world;};

	virtual void onEnterTransitionDidFinish();
	void menuBackCallback(cocos2d::Ref* pSender);
    
    void catchBack(Ore * ore);
    void startSway();

private:
	AirShip *airshipSprite;
	AirShipRope *airShipRopeSprite;
    Magnetite * magnetite;
    cocos2d::Sprite * ropeEndPointSpite;
    
	cocos2d::Sprite * ropeCloneSpite;

	cocos2d::Vector<Ore *> itemArr;

	cocos2d::Point ropeStartPoint;

	cocos2d::PhysicsWorld* m_world;

	bool isReady;

	void showItem();
    void removeScoreLabel(cocos2d::Label * scoreLabel);
    
    
    void update(float dTime);
    bool onContactBegin(const cocos2d::PhysicsContact& contact);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};



#endif /* __GAMEVIEW_SCENE_H__ */
