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

class GameView : public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameView);


	void onEnterTransitionDidFinish();
	void menuBackCallback(cocos2d::Ref* pSender);

private:
	AirShip *airshipSprite;
	cocos2d::Vector<cocos2d::Sprite*> itemArr;

	void showItem();
};



#endif /* __GAMEVIEW_SCENE_H__ */
