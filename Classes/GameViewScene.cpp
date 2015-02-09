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
#include "EllipseBy.h"


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
    
    earthLayer = new Earth();
	earthLayer->setPosition(visibleSize.width / 2 - earthLayer->getContentSize().width / 2 ,
			visibleSize.height * 0.6 - earthLayer->getContentSize().height);
    earthLayer->setPhyWorld(this->getPhysicsWorld());
    this->addChild(earthLayer, 1);
    
    earthTurn = false;
    
    auto bottomSprite = Sprite::create("bottom.png");
    bottomSprite->setAnchorPoint(Vec2(0 , 0));
    bottomSprite->setPosition(0, 0);
    this->addChild(bottomSprite, 2);

    
    auto goItem = MenuItemImage::create("go.png",
                                        "go.png",
                                        CC_CALLBACK_0(GameView::catchOre, this));
    
    float bottomY = goItem->getContentSize().height / 2 + 30;
    
    goItem->setPosition(Vec2(visibleSize.width - goItem->getContentSize().width / 2 - 30,
                             bottomY));
    
    auto propItem1 = MenuItemImage::create("prop.png",
                                          "prop.png",
                                          CC_CALLBACK_0(GameView::useProp, this, 1));
    float bottomX = propItem1->getContentSize().width / 2 + 30;
    
    propItem1->setPosition(Vec2(bottomX,
                               bottomY));
    
    auto propItem2 = MenuItemImage::create("prop.png",
                                           "prop.png",
                                           CC_CALLBACK_0(GameView::useProp, this, 2));
    bottomX += propItem2->getContentSize().width + 30;
    propItem2->setPosition(Vec2(bottomX,
                                bottomY));
    
    auto propItem3 = MenuItemImage::create("prop.png",
                                           "prop.png",
                                           CC_CALLBACK_0(GameView::useProp, this, 3));
    bottomX += propItem3->getContentSize().width + 30;
    propItem3->setPosition(Vec2(bottomX,
                                bottomY));
    
    auto bottomMenu = Menu::create(propItem1,propItem2, propItem3,goItem, NULL);
    bottomMenu->setPosition(Vec2::ZERO);
    this->addChild(bottomMenu, 3);
    
	return true;
}


void GameView::useProp(int propID) {
    log("useprop***********************%d", propID);
}

void GameView::catchOre() {
    log("####################catchOre");
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
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameView::startGame, this));
	Sequence *seq = Sequence::create(moveTo,fun,NULL);
	airshipSprite->runAction(seq);

	earthLayer->startTurn();
    earthTurn = true;
}


void GameView::startGame() {
    earthLayer->showOre();
    
    //椭圆旋转
	EllipseConfig config;
	config.ellipseA = 20;
	config.ellipseB = 40;
	config.cenPos = airshipSprite->getPosition();
	config.isAntiClockwise = true;
	config.startAngle = 0;
	config.selfAngle = 45;
    
	airshipSprite->runAction(RepeatForever::create(EllipseBy::create(2.5,config)));
    
    Sprite *trackSprite = Sprite::create("track_arc.png");
    trackSprite->setPosition(airshipSprite->getPosition().x, airshipSprite->getPosition().y - 100);
    this->addChild(trackSprite, 2);
    
    EllipseConfig config1;
	config1.ellipseA = 20;
	config1.ellipseB = 40;
	config1.cenPos = trackSprite->getPosition();
	config1.isAntiClockwise = true;
	config1.startAngle = 0;
	config1.selfAngle = 45;
    
	trackSprite->runAction(RepeatForever::create(EllipseBy::create(2.5,config1)));
    
    Sprite *trackPointSprite = Sprite::create("track_point.png");
    trackPointSprite->setPosition(trackSprite->getPosition());
    this->addChild(trackPointSprite, 3);
    
    PointArray *array = PointArray::create(20);
    array->addControlPoint(Vec2(0,0));
    array->addControlPoint(Vec2(-trackSprite->getContentSize().width / 2,0));
    array->addControlPoint(Vec2(0,-trackSprite->getContentSize().height / 2));
    array->addControlPoint(Vec2(trackSprite->getContentSize().width / 2,0));
    array->addControlPoint(Vec2(0,-trackSprite->getContentSize().height / 2));
    array->addControlPoint(Vec2(0,0));
    
    CardinalSplineBy *cardinalSplineBy = CardinalSplineBy::create(3.0f, array, 0);

    trackPointSprite->runAction(RepeatForever::create(cardinalSplineBy));
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
    
    if (earthTurn) {
        earthLayer->stopTurn();
        earthTurn = false;
    } else {
        earthLayer->startTurn();
        earthTurn = true;
    }
    
}
