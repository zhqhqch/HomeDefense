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
#include "Constants.h"
#include "MagnetiteSprite.h"

#include "iostream"


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
	if(!Layer::init()){
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
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
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

	airshipSprite = new AirShip(0, visibleSize.height * 0.7);
	airshipSprite->setVisible(false);
	this->addChild(airshipSprite, 2);

	Ore* itemA1 = new Ore("item_a_1.png", 100, 150, 20, 30);
	itemA1->setOpacity(0);
	itemA1->setTag(10);
	this->addChild(itemA1, 1);
	itemArr.pushBack(itemA1);

	Ore* itemA2 = new Ore("item_a_2.png", 400, 80, 30, 40);
	itemA2->setOpacity(0);
	itemA2->setTag(11);
	this->addChild(itemA2, 1);
	itemArr.pushBack(itemA2);

	Ore* itemA3 = new Ore("item_a_3.png", 500, 140, 50, 50);
	itemA3->setOpacity(0);
	itemA3->setTag(12);
	this->addChild(itemA3, 1);
	itemArr.pushBack(itemA3);


	Ore* itemB1 = new Ore("item_b_1.png", 300, 50, 30, 40);
	itemB1->setOpacity(0);
	itemB1->setTag(13);
	this->addChild(itemB1, 1);
	itemArr.pushBack(itemB1);

	Ore* itemB2 = new Ore("item_b_2.png", 300, 180, 40, 50);
	itemB2->setOpacity(0);
	itemB2->setTag(14);
	this->addChild(itemB2, 1);
	itemArr.pushBack(itemB2);

	Ore* itemB3 = new Ore("item_b_3.png", 720, 200, 50, 60);
	itemB3->setOpacity(0);
	itemB3->setTag(15);
	this->addChild(itemB3, 1);
	itemArr.pushBack(itemB3);

	Ore* itemC1 = new Ore("item_c_1.png", 1100, 10, 20, 30);
	itemC1->setOpacity(0);
	itemC1->setTag(16);
	this->addChild(itemC1, 1);
	itemArr.pushBack(itemC1);

	Ore* itemC2 = new Ore("item_c_2.png", 970, 180, 30, 40);
	itemC2->setOpacity(0);
	itemC2->setTag(17);
	this->addChild(itemC2, 1);
	itemArr.pushBack(itemC2);

	Ore* itemC3 = new Ore("item_c_3.png", 900, 140, 40, 50);
	itemC3->setOpacity(0);
	itemC3->setTag(18);
	this->addChild(itemC3, 1);
	itemArr.pushBack(itemC3);

    this->scheduleUpdate();
    
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

void GameView::update(float dTime){
//    CCLOG("****************");
    if(isReady){
        if(magnetite->isMove()){
            airShipRopeSprite->refreshRopeLen(magnetite->getPosition());
        }
    }
    
}

void GameView::startSway(){
    airShipRopeSprite->sway();
}

void GameView::showItem(){
	for(Ore* item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    
	ropeStartPoint = Point(visibleSize.width / 2, airshipSprite->getPosition().y - airshipSprite->getContentSize().height / 3);
    
	float catchAngle = atan2(ropeStartPoint.x,ropeStartPoint.y);
	catchAngle = CC_RADIANS_TO_DEGREES(catchAngle);
    
    
    magnetite = new Magnetite(this, ropeStartPoint.x, ropeStartPoint.y);
    this->addChild(magnetite,3);
    
    airShipRopeSprite = new AirShipRope(this,magnetite,ropeStartPoint.x, ropeStartPoint.y,catchAngle,true);
    this->addChild(airShipRopeSprite,3);
    
    magnetite->reach();
    
//    airShipRopeSprite = new AirShipRope(this,magnetite,ropeStartPoint.x, ropeStartPoint.y,catchAngle,true);
//	this->addChild(airShipRopeSprite,3);
    
//	airShipRopeSprite->reachProbe();

//	ropeCloneSpite = Sprite::create("line.png");
//	ropeCloneSpite->setPosition(ropeStartPoint.x, ropeStartPoint.y);
//	auto body = PhysicsBody::createBox(ropeCloneSpite->getContentSize());
//	body->setDynamic(false);
//	body->setContactTestBitmask(0x0001);
//	body->setCategoryBitmask(0x0001);
//	body->setCollisionBitmask(0x0001);
//	body->setGravityEnable(false);
//	ropeCloneSpite->setPhysicsBody(body);
//	this->addChild(ropeCloneSpite, 3);
    
    isReady = true;
}


void GameView::menuBackCallback(Ref* pSender){
	auto mainView = MainView::createScene();
	TransitionUtil::backScene(mainView);
}


bool GameView::onContactBegin(const PhysicsContact& contact){
	CCLog("=========================$$$$$$$$$$$$$$");
	Ore * target = (Ore  *)contact.getShapeA()->getBody()->getNode();
	CCLog("$$$$$$$%d", target->getTag());
	airShipRopeSprite->hookBack(target->getPosition(), target);
	return true;
}

bool GameView::onTouchBegan(Touch *touch, Event *unused_event) {
    return isReady;
}

void GameView::onTouchMoved(Touch *touch, Event *unused_event) {
}

void GameView::onTouchEnded(Touch *touch, Event *unused_event) {

    Point target = airShipRopeSprite->grab();
    CCLog("%f$$$$$$$$$%f", target.x, target.y);
    if(!target.equals(kPintNull)){
//    	ropeCloneSpite->setRotation(airShipRopeSprite->getRotation());
    	airShipRopeSprite->catchRock(target);
    }
}


void GameView::catchBack(Ore * ore) {
    ore->removeFromParentAndCleanup(true);
    itemArr.eraseObject(ore);
    
    CCLOG("add score===%i", ore->getScore());

    std::stringstream ss;
    ss<<"+";
    ss<<ore->getScore();
    std::string text = ss.str();
    
    Label *scoreLable = Label::create();
    scoreLable->setString(text);
    scoreLable->setSystemFontSize(21);
    scoreLable->setColor(Color3B::RED);
    scoreLable->setPosition(airshipSprite->getPosition().x, airshipSprite->getPosition().y + 100);
    this->addChild(scoreLable);
    
    MoveTo * moveTo = MoveTo::create(2.0f, Vec2(scoreLable->getPosition().x, scoreLable->getPosition().y + 100));
    FadeOut * fadeOut = FadeOut::create(2.0f);
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameView::removeScoreLabel, this, scoreLable));
	Sequence *seq = Sequence::create(moveTo,fadeOut,fun,NULL);
    scoreLable->runAction(seq);
}

void GameView::removeScoreLabel(Label * scoreLabel) {
    scoreLabel->removeFromParentAndCleanup(true);
}
