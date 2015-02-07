/*
 * GameViewScene.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "GameViewScene.h"
#include "TransitionUtil.h"
#include "MainViewScene.h"
#include "Constants.h"


USING_NS_CC;

Scene * GameView::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameView::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool GameView::init(){
	if(!Scene::init()){
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();       //单点触摸
	//auto listener = EventListenerTouchAllAtOnce::create();      //多点触摸
	//setTouchEnabled(true);        //3.0版本已经被弃用

	//触屏事件
	listener->onTouchBegan = CC_CALLBACK_2(GameView::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameView::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//碰撞事件
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameView::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->setContactTestBitmask(0x0001);
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	edgeNode->setTag(kWallTag);
	this->addChild(edgeNode);

	Label * backLable = Label::create();
	backLable->setString("返回");
	backLable->setSystemFontSize(48);

	auto backItem = MenuItemLabel::create(backLable,
			CC_CALLBACK_1(GameView::menuBackCallback, this));
	backItem->setPosition(Vec2(backItem->getContentSize().width / 2 + 38,
			visibleSize.height - backItem->getContentSize().height / 2 - 33));

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto gameBgSprite = Sprite::create("game_bg.jpg");
	gameBgSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(gameBgSprite, 0);


	airshipSprite = new AirShip(visibleSize.width / 2, visibleSize.height);
	airshipSprite->setVisible(false);
	this->addChild(airshipSprite, 2);

	earthLayer = new Earth(visibleSize.width/2, visibleSize.height * 0.05f);
	this->addChild(earthLayer, 1);

	return true;
}


void GameView::menuBackCallback(Ref* pSender){
	auto mainView = MainView::createScene();
	TransitionUtil::backScene(mainView);
}


//过场动画结束后调用
void GameView::onEnterTransitionDidFinish(){
	log("#########################3");
	airshipSprite->setVisible(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	MoveTo *moveTo = MoveTo::create(2.0f, Vec2(visibleSize.width / 2, visibleSize.height * 0.7));
	airshipSprite->runAction(moveTo);
}

void GameView::update(float dTime){
	log("@@@@@@@@@@@@@@@@@@@@@@@@@");
}

bool GameView::onContactBegin(const PhysicsContact& contact){
	log("^^^^^^^^^^^^^^^^^^^^");

	return true;
}

bool GameView::onTouchBegan(Touch *touch, Event *unused_event) {
    return true;
}

void GameView::onTouchMoved(Touch *touch, Event *unused_event) {
}

void GameView::onTouchEnded(Touch *touch, Event *unused_event) {
	log("########$$$$$$$$$$$");
}
