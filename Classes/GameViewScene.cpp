/*
 * GameViewScene.cpp
 *
 *  Created on: 2015年1月12日
 *      Author: hqch
 */

#include "GameViewScene.h"
#include "TransitionUtil.h"
#include "MainViewScene.h"
#include "AirShipSprite.h"


USING_NS_CC;


Scene * GameView::createScene() {
	auto scene = Scene::create();
	auto layer = GameView::create();

	scene->addChild(layer);

	return scene;
}


bool GameView::init(){
	if(!Layer::init()){
		return false;
	}
    
    auto listener = EventListenerTouchOneByOne::create();       //单点触摸
    //auto listener = EventListenerTouchAllAtOnce::create();      //多点触摸
    //setTouchEnabled(true);        //3.0版本已经被弃用
    
    listener->onTouchBegan = CC_CALLBACK_2(GameView::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameView::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameView::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto backItem = MenuItemLabel::create(Label::create("返回", "宋体", 48),
			CC_CALLBACK_1(GameView::menuBackCallback, this));
	backItem->setPosition(Vec2(backItem->getContentSize().width / 2 + 38,
			visibleSize.height - backItem->getContentSize().height / 2 - 33));

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto gameBgSprite = Sprite::create("game_bg.jpg");
	gameBgSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(gameBgSprite, 0);

	airshipSprite = new AirShip(0, visibleSize.height * 0.7);
	airshipSprite->setVisible(false);
	this->addChild(airshipSprite, 2);

	auto itemA1 = Sprite::create("item_a_1.png");
	itemA1->setPosition(Vec2(100, 150));
	itemA1->setOpacity(0);
	this->addChild(itemA1, 1);
	itemArr.pushBack(itemA1);

	auto itemA2 = Sprite::create("item_a_2.png");
	itemA2->setPosition(Vec2(400, 80));
	itemA2->setOpacity(0);
	this->addChild(itemA2, 1);
	itemArr.pushBack(itemA2);

	auto itemA3 = Sprite::create("item_a_3.png");
	itemA3->setPosition(Vec2(500, 140));
	itemA3->setOpacity(0);
	this->addChild(itemA3, 1);
	itemArr.pushBack(itemA3);


	auto itemB1 = Sprite::create("item_b_1.png");
	itemB1->setPosition(Vec2(300, 50));
	itemB1->setOpacity(0);
	this->addChild(itemB1, 1);
	itemArr.pushBack(itemB1);

	auto itemB2 = Sprite::create("item_b_2.png");
	itemB2->setPosition(Vec2(300, 180));
	itemB2->setOpacity(0);
	this->addChild(itemB2, 1);
	itemArr.pushBack(itemB2);

	auto itemB3 = Sprite::create("item_b_3.png");
	itemB3->setPosition(Vec2(720, 200));
	itemB3->setOpacity(0);
	this->addChild(itemB3, 1);
	itemArr.pushBack(itemB3);


	auto itemC1 = Sprite::create("item_c_1.png");
	itemC1->setPosition(Vec2(1100, 10));
	itemC1->setOpacity(0);
	this->addChild(itemC1, 1);
	itemArr.pushBack(itemC1);

	auto itemC2 = Sprite::create("item_c_2.png");
	itemC2->setPosition(Vec2(970, 180));
	itemC2->setOpacity(0);
	this->addChild(itemC2, 1);
	itemArr.pushBack(itemC2);

	auto itemC3 = Sprite::create("item_c_3.png");
	itemC3->setPosition(Vec2(900, 140));
	itemC3->setOpacity(0);
	this->addChild(itemC3, 1);
	itemArr.pushBack(itemC3);

	return true;
}

//过场动画结束后调用
void GameView::onEnterTransitionDidFinish(){
	airshipSprite->setVisible(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	ActionInterval *moveTo = MoveTo::create(2.0f, Vec2(visibleSize.width/2, visibleSize.height * 0.7));
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameView::showItem, this));
	Sequence *seq = Sequence::create(moveTo,fun,NULL);
	airshipSprite->runAction(seq);
}

void GameView::showItem(){
	for(auto item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}

	airshipSprite->showRope();
}


void GameView::menuBackCallback(Ref* pSender){
	auto mainView = MainView::createScene();
	TransitionUtil::backScene(mainView);
}



bool GameView::onTouchBegan(Touch *touch, Event *unused_event) {
    CCLOG("===========onTouchBegan");
    return true;
}


void GameView::onTouchMoved(Touch *touch, Event *unused_event) {
    CCLOG("@@@@@@@@@@@@@onTouchMoved");
}

void GameView::onTouchEnded(Touch *touch, Event *unused_event) {
    CCLOG("^^^^^^^^^^^^onTouchEnded");
    
    airshipSprite->grab();
    
}

