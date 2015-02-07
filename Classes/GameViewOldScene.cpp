/*
 * GameViewOldScene.cpp
 *
 *  Created on: 2015年1月12日
 *      Author: hqch
 */

#include "GameViewOldScene.h"
#include "TransitionUtil.h"
#include "MainViewScene.h"
#include "AirShipSprite.h"
#include "Constants.h"
#include "MagnetiteSprite.h"
#include "LightLineRender.h"
#include "Vec2Util.h"

#include "iostream"


USING_NS_CC;


Scene * GameViewOld::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameViewOld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}


bool GameViewOld::init(){
	if(!Layer::init()){
		return false;
	}
    
    
    auto listener = EventListenerTouchOneByOne::create();       //单点触摸
    //auto listener = EventListenerTouchAllAtOnce::create();      //多点触摸
    //setTouchEnabled(true);        //3.0版本已经被弃用
    
    //触屏事件
    listener->onTouchBegan = CC_CALLBACK_2(GameViewOld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameViewOld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameViewOld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//碰撞事件
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameViewOld::onContactBegin, this);
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
			CC_CALLBACK_1(GameViewOld::menuBackCallback, this));
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

	Ore* itemA1 = new Ore("item_a_1.png", 100, 150, 20, 3);
	itemA1->setOpacity(0);
	itemA1->setTag(10);
	this->addChild(itemA1, 1);
	itemArr.pushBack(itemA1);

	Ore* itemA2 = new Ore("item_a_2.png", 400, 80, 30, 4);
	itemA2->setOpacity(0);
	itemA2->setTag(11);
	this->addChild(itemA2, 1);
	itemArr.pushBack(itemA2);

	Ore* itemA3 = new Ore("item_a_3.png", 500, 140, 50, 5);
	itemA3->setOpacity(0);
	itemA3->setTag(12);
	this->addChild(itemA3, 1);
	itemArr.pushBack(itemA3);


	Ore* itemB1 = new Ore("item_b_1.png", 300, 50, 30, 4);
	itemB1->setOpacity(0);
	itemB1->setTag(13);
	this->addChild(itemB1, 1);
	itemArr.pushBack(itemB1);

	Ore* itemB2 = new Ore("item_b_2.png", 300, 180, 40, 5);
	itemB2->setOpacity(0);
	itemB2->setTag(14);
	this->addChild(itemB2, 1);
	itemArr.pushBack(itemB2);

	Ore* itemB3 = new Ore("item_b_3.png", 720, 200, 50, 6);
	itemB3->setOpacity(0);
	itemB3->setTag(15);
	this->addChild(itemB3, 1);
	itemArr.pushBack(itemB3);

	Ore* itemC1 = new Ore("item_c_1.png", 1100, 10, 20, 3);
	itemC1->setOpacity(0);
	itemC1->setTag(16);
	this->addChild(itemC1, 1);
	itemArr.pushBack(itemC1);

	Ore* itemC2 = new Ore("item_c_2.png", 970, 180, 30, 4);
	itemC2->setOpacity(0);
	itemC2->setTag(17);
	this->addChild(itemC2, 1);
	itemArr.pushBack(itemC2);

	Ore* itemC3 = new Ore("item_c_3.png", 900, 140, 40, 5);
	itemC3->setOpacity(0);
	itemC3->setTag(18);
	this->addChild(itemC3, 1);
	itemArr.pushBack(itemC3);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//线条容器
	std::vector<LightLineRender::Line> lines;
	//设置线条位置
	//第一段闪电的起点和终点
	Vec3 segStart = Vec3(-50,-50,-8);
	Vec3 segEnd   = Vec3(50,50,-8);
	lines.push_back( LightLineRender::Line( segStart, segEnd, 0 ) );
	//第二段闪电的起点和终点
	segStart = Vec3(50,50,-8);
	segEnd   = Vec3(-50,50,-8);
	lines.push_back( LightLineRender::Line( segStart, segEnd, 0 ) );
	//第三段闪电的起点和终点
	segStart = Vec3(-50,50,-8);
	segEnd   = Vec3(50,-50,-8);
	lines.push_back( LightLineRender::Line( segStart, segEnd, 0 ) );
	//第四段闪电的起点和终点
	segStart = Vec3(50,-50,-8);
	segEnd   = Vec3(0,100,-8);
	lines.push_back( LightLineRender::Line( segStart, segEnd, 0 ) );
	//第五段闪电的起点和终点
	segStart = Vec3(0,100,-8);
	segEnd   = Vec3(-50,-50,-8);
	lines.push_back( LightLineRender::Line( segStart, segEnd, 0 ) );
	//创建出闪光链
	LightLineRender*	_lighting = LightLineRender::create();
	//设置不需要强制纹理循环
    _lighting->setForceTexLoop( false );
	//设置宽
	_lighting->setWidth( 120 );
	//设置 单张纹理长度，调整这个数值可以避免纹理过度拉伸或挤压
	_lighting->setTextueLength( 100 );
	//设置单个面片网格长，越小曲线越平滑，数值过于小可能带来效率问题
	_lighting->setStep( 10 );
	//设置振幅1
	_lighting->setAmplitude0( 4 );
	//设置频率1
	_lighting->setFrequency0( 500 );
	//设置振幅2
	_lighting->setAmplitude1( 1 );
	//设置频率2
	_lighting->setFrequency1( 400 );
	//设置
	_lighting->setTimeFactor( 0.5 );
	//使用线段容器创建闪电链
	_lighting->setLines( lines );
	//使用柏林噪音算法
	_lighting->setLineType( LineType::LT_PerlinNosie );
	//设置每帧强制更新重建模型
	_lighting->setForceUpdate(true);

	_lighting->setPosition(Vec2(visibleSize.width / 4 + origin.x,visibleSize.height / 2 + origin.y));
	_lighting->setOpacity(0);
	//将闪电链加入到当前层中.
	this->addChild(_lighting,0,kLightLineTag);


	isCatch = false;

    this->scheduleUpdate();
    
	return true;
}

//过场动画结束后调用
void GameViewOld::onEnterTransitionDidFinish(){
	airshipSprite->setVisible(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	ActionInterval *moveTo = MoveTo::create(2.0f, Vec2(visibleSize.width/2, visibleSize.height * 0.7));
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameViewOld::showItem, this));
	Sequence *seq = Sequence::create(moveTo,fun,NULL);
	airshipSprite->runAction(seq);
}

void GameViewOld::update(float dTime){
    if(isReady){
        if(magnetite->isMove()){
            airShipRopeSprite->refreshRopeLen(magnetite->getPosition(),
            		magnetite->isReach(), magnetite->isBack());
        }

//        if(airShipRopeSprite->isSway()){
            magnetite->startFollow(airShipRopeSprite->getRopeEndPoint());
//        }
        

        if(isCatch){
        	targetOre->startFollow(magnetite, airShipRopeSprite->getRotation());
        }
    }
    
}

void GameViewOld::startSway(){
    isStart = true;
    log("rope end##########%f", airShipRopeSprite->getContentSize().height);
    airShipRopeSprite->sway();
}

void GameViewOld::showItem(){
	for(Ore* item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    
	ropeStartPoint = Point(visibleSize.width / 2, airshipSprite->getPosition().y - airshipSprite->getContentSize().height / 3);
    
	catchAngle = atan2(ropeStartPoint.x,ropeStartPoint.y);
	catchAngle = CC_RADIANS_TO_DEGREES(catchAngle);
    
    airShipRopeSprite = new AirShipRope(this, ropeStartPoint.x, ropeStartPoint.y,catchAngle);
    this->addChild(airShipRopeSprite,3);
    
    magnetite = new Magnetite(this, ropeStartPoint.x, ropeStartPoint.y);
    this->addChild(magnetite,3);

    
    magnetite->reach();

    isReady = true;
}


void GameViewOld::menuBackCallback(Ref* pSender){
	auto mainView = MainView::createScene();
	TransitionUtil::backScene(mainView);
}


bool GameViewOld::onContactBegin(const PhysicsContact& contact){
	if(isCatch){
		return true;
	}
	auto sp1 = (Sprite *)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Sprite *)contact.getShapeB()->getBody()->getNode();
	log("****************************");
	if(sp1->getTag() > 0 && sp1->getTag() != kWallTag){
		targetOre = (Ore *) sp1;
		isCatch = true;
		magnetite->backWithOreToStartPoint();
	} else if(sp2->getTag() > 0 && sp2->getTag() != kWallTag){
		targetOre = (Ore *) sp2;
		isCatch = true;
		magnetite->backWithOreToStartPoint();
	} else if(sp1->getTag() == kWallTag || sp2->getTag() == kWallTag){
        magnetite->backToStartPoint();
    }

	return true;
}

bool GameViewOld::onTouchBegan(Touch *touch, Event *unused_event) {
    return isReady;
}

void GameViewOld::onTouchMoved(Touch *touch, Event *unused_event) {
}

void GameViewOld::onTouchEnded(Touch *touch, Event *unused_event) {
	isCatch = false;
    Point target = airShipRopeSprite->grab();
    if(target.equals(kPintNull)){
    	return;
    }

    log("rope start##########%f", airShipRopeSprite->getContentSize().height);
    magnetite->moveToPoint(airShipRopeSprite->getRopeEndPoint(), target);


	auto    visibleSize = Director::getInstance()->getVisibleSize();
	auto	origin = Director::getInstance()->getVisibleOrigin();
	//线条容器
	std::vector<LightLineRender::Line> lines;
	//设置线条位置

	//闪电的起点和终点
	Vec2	tFishPos(Vec2(visibleSize / 2) + origin);
	tFishPos = airShipRopeSprite->getPosition() + origin;
	Vec3 segStart = Vec3(0,0,-8);
//	Vec2 touchLocation = touch->getLocation();
//	Vec3 segEnd   = Vec3(touchLocation.x - tFishPos.x ,touchLocation.y - tFishPos.y ,-8);
	Vec2 temp = getIntersectPoint(target);
	Vec3 segEnd = Vec3(temp.x - tFishPos.x, temp.y - tFishPos.y, -8);

	log("%f^^^^^^%f^^^^^%f^^^^%f", target.x, target.y,temp.x, temp.y);

	//取得方向
	Vec3  dir = segEnd - segStart ;
	float fLength = dir.length();
	dir.normalize();
	//顺时针转动45度形成一个偏移点做为第一个闪电链线段。
	Vec3  rotate_left;
	Mat4  rotate_left_Mat;
	kmMat4RotationZ(&rotate_left_Mat,MATH_DEG_TO_RAD(-45));
	kmVec3TransformCoord(&rotate_left,&dir,&rotate_left_Mat);
	rotate_left.normalize();
	//逆时针转动45度形成一个偏移点做为第一个闪电链线段。
	Vec3  rotate_right;
	Mat4  rotate_right_Mat;
	kmMat4RotationZ(&rotate_right_Mat,MATH_DEG_TO_RAD(45));
	kmVec3TransformCoord(&rotate_right,&dir,&rotate_right_Mat);
	rotate_right.normalize();


	//分成三段闪电链
	Vec3  v1_s = segStart ;
	Vec3  v1_e = segStart + dir * fLength / 4.0 + rotate_left * (fLength / 6.0);

	Vec3  v2_s = v1_e ;
	Vec3  v2_e = segStart + dir * fLength / 2.0 + rotate_right * (fLength / 6.0);

	Vec3  v3_s = v2_e ;
	Vec3  v3_e = segEnd;

	lines.push_back( LightLineRender::Line( v1_s, v1_e, 0 ) );
	lines.push_back( LightLineRender::Line( v2_s, v2_e, 0 ) );
	lines.push_back( LightLineRender::Line( v3_s, v3_e, 0 ) );

	//创建出闪光链
	LightLineRender*	_lighting = dynamic_cast<LightLineRender*>(getChildByTag(kLightLineTag));
	//使用线段容器创建闪电链
	_lighting->setLines( lines );
	_lighting->setPosition(tFishPos);
	//这一句可以让闪电链在1秒内渐渐消隐。它通过调节Shader中的u_color值从1变为0来实现。
	_lighting->OpenAlphaToZero(1.0);
}


Vec2 GameViewOld::getIntersectPoint(Vec2 target) {
	float rotation = airShipRopeSprite->getRotation();
	bool threeQuadrant;
	bool isVertical;

	if(rotation > 0){
		threeQuadrant = true;
		if(rotation <= catchAngle){
			isVertical = false;
		} else {
			isVertical = true;
		}
	} else if(rotation < 0){
		threeQuadrant = false;
		if(rotation <= -catchAngle){
			isVertical = true;
		}else{
			isVertical = false;
		}
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 start = airShipRopeSprite->getRopeStartPoint();
	Vec2 end1 = Vec2(0,0);
	Vec2 end2 = Vec2(0,0);
	if (threeQuadrant) {
		if(isVertical){
            end1 = Vec2(0,visibleSize.height);
			end2 = Vec2(0,0);
		} else {
            end1 = Vec2(0, 0);
			end2 = Vec2(visibleSize.width,0);
		}
	} else {
		if(isVertical){
			end1 = Vec2(visibleSize.width,0);
			end2 = Vec2(visibleSize.width, visibleSize.height);
		} else {
			end1 = Vec2(0, 0);
			end2 = Vec2(visibleSize.width, 0);
		}
	}

    return Vec2Util::getIntersectPoint(start, target, end1, end2);
}


void GameViewOld::catchBack() {
    targetOre->removeFromParentAndCleanup(true);
    itemArr.eraseObject(targetOre);
    
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
    CallFunc *fun = CallFunc::create(CC_CALLBACK_0(GameViewOld::removeScoreLabel, this, scoreLable));
	Sequence *seq = Sequence::create(moveTo,fadeOut,fun,NULL);
    scoreLable->runAction(seq);
}

void GameViewOld::removeScoreLabel(Label * scoreLabel) {
    scoreLabel->removeFromParentAndCleanup(true);
}

void GameViewOld::stopMagnetite() {
	magnetite->stopMove();
}
