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
#include "PropMenuItemSprite.h"
#include "EncyptUtil.h"
#include "DataUtil.h"
#include "Checkpoint.h"
#include "AnimationUtil.h"


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
    
    isReady = false;
    isPause = false;

    std::string s = EncyptUtil::encrypt("胡七号sdfdsds");
    log("========%s", s.c_str());
    std::string s1 = EncyptUtil::decrypt(s);
    log("====########====%s", s1.c_str());

    DataUtil::saveInt("test", 100);
    int a = DataUtil::getIntForKey("test");
    log("!!!!!!!!!!%d", a);
    log("file path:%s", UserDefault::getXMLFilePath().c_str());

    checkpoint = new Checkpoint(1);
    Checkpoint::BgData * bgData = checkpoint->bgArray.at(0);
    Checkpoint::ItemData * itemData = checkpoint->itemArray.at(0);

    log("%d&&&&&&&%f===%s====%s", checkpoint->id,
    		checkpoint->layer1Speed, bgData->imageName.c_str(), itemData->imageName.c_str());

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

	Label * backLable = Label::create();
	backLable->setString("返回");
	backLable->setSystemFontSize(48);

	auto backItem = MenuItemLabel::create(backLable,
			CC_CALLBACK_1(GameView::menuBackCallback, this));
	backItem->setPosition(Vec2(backItem->getContentSize().width / 2 + 38,
			visibleSize.height - backItem->getContentSize().height / 2 - 33));

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, kGameUIZOrder);

	auto gameBgSprite = Sprite::create("game-bg.jpg");
	gameBgSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(gameBgSprite);

    //加载纹理
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", "game.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("checkpoint1.plist", "checkpoint1.pvr.ccz");
    //初始化动画
    AnimationUtil::createAnimationByName(Value(pitFallenRockAnimationName),
                                         Value(pitFallenRockAnimationPrefixStr),
                                         pitFallenRockAnimationCount);
    
    AnimationUtil::createAnimationByName(Value(catchedFailAnimationName),
                                         Value(catchedFailAnimationPrefixStr),
                                         catchedFailAnimationCount);
    
    AnimationUtil::createAnimationByName(Value(catchedSuccessAnimationName),
                                         Value(catchedSuccessAnimationPrefixStr),
                                         catchedSuccessAnimationCount);
    
    AnimationUtil::createAnimationByName(Value(catchingAnimationName),
                                         Value(catchingAnimationPrefixStr),
                                         catchingAnimationCount);


	airshipSprite = new AirShip(visibleSize.width / 2, visibleSize.height);
	airshipSprite->setVisible(false);
	this->addChild(airshipSprite, kAirShipZOrder);

    earthLayer = new Earth(this, checkpoint);
	earthLayer->setPosition(visibleSize.width / 2 - earthLayer->getContentSize().width / 2 ,
			visibleSize.height * 0.65 - earthLayer->getContentSize().height);
    earthLayer->setPhyWorld(this->getPhysicsWorld());
    this->addChild(earthLayer, kEarthZOrder);
    
    shipMove = false;
    
    auto bottomSprite = Sprite::createWithSpriteFrameName("controlui-bottom.png");
    bottomSprite->setAnchorPoint(Vec2(0 , 0));
    bottomSprite->setPosition(0, 0);
    this->addChild(bottomSprite, kGameUIZOrder);

    auto pauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause.png"),
                                 Sprite::createWithSpriteFrameName("pause-selected.png"),
                                 CC_CALLBACK_0(GameView::pauseGame, this));
    
    float bottomX = pauseItem->getContentSize().width / 2 + 30;
    float bottomY = pauseItem->getContentSize().height / 2 + 30;
    
    pauseItem->setPosition(Vec2(bottomX, bottomY));
    

    
    PropSprite *speedItem = new PropSprite(kSpeedProp, 0, "speed");
    bottomX += speedItem->getContentSize().width / 2 + 150;
    speedItem->setPosition(Vec2(bottomX,bottomY));
    
    
    PropSprite *bombItem = new PropSprite(kBombProp, 10, "bomb");
    bottomX += bombItem->getContentSize().width + 30;
    bombItem->setPosition(Vec2(bottomX,
                                bottomY));
    
    PropSprite *timeItem = new PropSprite(kTimeProp, 103, "time");
    bottomX += timeItem->getContentSize().width + 30;
    timeItem->setPosition(Vec2(bottomX,
                                bottomY));
    
    auto bottomMenu = Menu::create(pauseItem, speedItem, bombItem, timeItem, NULL);
    bottomMenu->setPosition(Vec2::ZERO);
    this->addChild(bottomMenu, kGameUIZOrder);
    
    float x = visibleSize.width;
    float y = visibleSize.height - bottomSprite->getContentSize().height;
    
    auto body = PhysicsBody::createEdgeBox(Size(x, y), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->setContactTestBitmask(0x0001);
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2 + bottomSprite->getContentSize().height / 2));
	edgeNode->setPhysicsBody(body);
	edgeNode->setTag(kWallTag);
	this->addChild(edgeNode);
    
    
    magnetite = new Magnetite(this, 0, 0);
    this->addChild(magnetite, kMagnetiteZOrder);
    
    
    this->scheduleUpdate();
    
	return true;
}


void GameView::useProp(int propID) {
    log("useprop***********************%d", propID);
}

void GameView::pauseGame() {
    log("####################pauseGame");
    if (isPause) {
        this->pause();
        Director::getInstance()->pause();
        isPause = true;
    } else {
        Director::getInstance()->resume();
        isPause = false;
    }
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

	MoveTo *moveTo = MoveTo::create(2.0f, Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameView::startGame, this));
	Sequence *seq = Sequence::create(moveTo,fun,NULL);
	airshipSprite->runAction(seq);

	earthLayer->startTurn();
}


void GameView::startGame() {
    earthLayer->showOre();
    
    airshipSprite->makeCurPosition();
	airshipSprite->startMove();
    airshipSprite->eyeLookDown();
    shipMove = true;
    
    trackSprite = Sprite::create("track_arc.png");
    trackSprite->setPosition(airshipSprite->getPosition().x, airshipSprite->getPosition().y - 100);
    this->addChild(trackSprite, kAirShipZOrder);

    
    trackPointSprite = Sprite::create("track_point.png");
    float x = trackSprite->getPosition().x;
    float y = trackSprite->getPosition().y;
    y -= 20;
    trackPointSprite->setPosition(x, y);
    this->addChild(trackPointSprite, kAirShipZOrder);
    
    
    float point1X = trackSprite->getPosition().x - trackSprite->getContentSize().width / 2;
    float point1Y = trackSprite->getPosition().y + trackSprite->getContentSize().height - 22;
    
    float point2X = trackSprite->getPosition().x - trackSprite->getContentSize().width / 4;
    float point2Y = trackSprite->getPosition().y + trackSprite->getContentSize().height / 2 - 35;

    float point3X = point2X + trackSprite->getContentSize().width / 2;
    float point3Y = point2Y;

    
    float endX = point1X + trackSprite->getContentSize().width;
    float endY = point1Y;
    
    float curX = trackPointSprite->getPosition().x;
    float curY = trackPointSprite->getPosition().y;
    
//    PointArray *array = PointArray::create(20);
//    array->addControlPoint(Vec2(0,0));
//    array->addControlPoint(Vec2(point2X - curX, point2Y - curY));
//    array->addControlPoint(Vec2(point1X - curX, point1Y - curY));
//    array->addControlPoint(Vec2(point2X - curX, point2Y - curY));
//    array->addControlPoint(Vec2(0,0));
//    array->addControlPoint(Vec2(point3X - curX, point3Y - curY));
//    array->addControlPoint(Vec2(endX - curX, endY - curY));
//    array->addControlPoint(Vec2(point3X - curX, point3Y - curY));
//    array->addControlPoint(Vec2(0,0));
//    CardinalSplineBy *cardinalSplineBy = CardinalSplineBy::create(8.0f, array, 0);
//    trackPointSprite->runAction(RepeatForever::create(cardinalSplineBy));
    
    PointArray *array = PointArray::create(20);
    array->addControlPoint(Vec2(curX,curY));
    array->addControlPoint(Vec2(point2X, point2Y));
    array->addControlPoint(Vec2(point1X, point1Y));
    array->addControlPoint(Vec2(point2X, point2Y));
    array->addControlPoint(Vec2(curX,curY));
    array->addControlPoint(Vec2(point3X, point3Y));
    array->addControlPoint(Vec2(endX, endY));
    array->addControlPoint(Vec2(point3X, point3Y));
    array->addControlPoint(Vec2(curX,curY));
    CardinalSplineTo *cardinalSplineTo = CardinalSplineTo::create(8.0f, array, 0);
    trackPointSprite->runAction(RepeatForever::create(cardinalSplineTo));
    
    isReady = true;
}

void GameView::update(float dTime){
    if (isReady) {
        if(magnetite->isMove()){
            airShipRopeSprite->refreshRopeLen(magnetite->getPosition(),
                                              magnetite->isReach(), magnetite->isBack());
            if(!isCatch){
            	isCatch = earthLayer->isCatchOre(magnetite->getPosition(), magnetite->getContentSize().width / 2);
				if(isCatch && !magnetite->isBack()){
					magnetite->backToStartPoint();
//					earthLayer->catchOreToAirShip(airshipSprite->getPosition());
				}
            }

        }
        if (magnetite->isBack()) {
            bool backEnd = airshipSprite->getBoundingBox().intersectsRect(magnetite->getBoundingBox());
            if (backEnd && !shipMove) {
                airShipRopeSprite->removeFromParentAndCleanup(true);
                magnetite->hide();
                airshipSprite->startMove();
                shipMove = true;
                trackSprite->setVisible(true);
                trackPointSprite->setVisible(true);
                trackPointSprite->resume();
                
                catchBack(isCatch);
            }
        }
        
        if(shipMove){
            Point curAirShipPoint = airshipSprite->getPosition();
            Point curTrackPoint = trackPointSprite->getPosition();
            Point tmp = curAirShipPoint - curTrackPoint;
            tmp.normalize();
            trackAngle = atan2(tmp.x,tmp.y);
            trackAngle = CC_RADIANS_TO_DEGREES(trackAngle);
            
            airshipSprite->eyeLook(trackAngle);
        }
    }
	
}

bool GameView::onContactBegin(const PhysicsContact& contact){
    if (isCatch) {
        return true;
    }
	log("^^^^^^^^^^^^^^^^^^^^");
	auto sp1 = (Sprite *)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Sprite *)contact.getShapeB()->getBody()->getNode();
	if(sp1->getTag() == kWallTag || sp2->getTag() == kWallTag){
        magnetite->backToStartPoint();
    }
	return true;
}

bool GameView::onTouchBegan(Touch *touch, Event *unused_event) {
    return isReady;
}

void GameView::onTouchMoved(Touch *touch, Event *unused_event) {
}

void GameView::onTouchEnded(Touch *touch, Event *unused_event) {
    if(magnetite->isMove()){
        return;
    }
    
	log("########$$$$$$$$$$$");
    
    if (shipMove) {
//        earthLayer->stopTurn();
        airshipSprite->stopMove();
        shipMove = false;
        trackSprite->setVisible(false);
        trackPointSprite->setVisible(false);
        trackPointSprite->pause();
        
        Point curAirShipPoint = airshipSprite->getPosition();
        magnetite->show();
        magnetite->moveToPoint(curAirShipPoint, trackPointSprite->getPosition());

        Point curTrackPoint = trackPointSprite->getPosition();
        Point tmp = curAirShipPoint - curTrackPoint;
        tmp.normalize();
        
        float catchAngle = atan2(tmp.x,tmp.y);
        catchAngle = CC_RADIANS_TO_DEGREES(catchAngle);
        airShipRopeSprite = new AirShipRope(this, curAirShipPoint.x,curAirShipPoint.y,catchAngle);
        this->addChild(airShipRopeSprite, kAirShipZOrder - 1);
        
        
        airshipSprite->playCatchAnimation();
        
    } else {
//        earthLayer->startTurn();
        airshipSprite->startMove();
        shipMove = true;
        trackSprite->setVisible(true);
        trackPointSprite->setVisible(true);
        trackPointSprite->resume();
        
        airShipRopeSprite->removeFromParentAndCleanup(true);
    }
}


void GameView::catchOreToAirShip(Ore * ore){
	Point p = Point(ore->getPositionX(), ore->getPositionY());
    Point tmp = ore->convertToWorldSpace(ore->getAnchorPointInPoints());
	targetOre = new Ore(ore->getImageName(), tmp.x, tmp.y, ore->getRotation(), ore->getScore(), ore->getWeight());
	this->addChild(targetOre, kMagnetiteZOrder);

    Point target = airshipSprite->convertToWorldSpace(airshipSprite->getAnchorPointInPoints());
    
	MoveTo * moveTo = MoveTo::create(5.0, target);
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameView::catchBack, this, true));
	Sequence * seq = Sequence::create(moveTo, fun, NULL);
	targetOre->runAction(seq);
}

void GameView::catchBack(bool success) {
    if(!success){
        airshipSprite->playCatchedFailAnimation();
        return;
    }
    
    airshipSprite->playCatchedSuccessAnimation();
    
	targetOre->removeFromParentAndCleanup(true);

	std::stringstream ss;
	ss<<"+";
	ss<<targetOre->getScore();
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

	isCatch = false;
}

void GameView::removeScoreLabel(Label * scoreLabel) {
    scoreLabel->removeFromParentAndCleanup(true);
}
