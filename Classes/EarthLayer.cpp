/*
 * EarthLayer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "EarthLayer.h"


USING_NS_CC;


Earth::Earth(){
	init();
}

bool Earth::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

    layer1 = Sprite::create();
    layer1->setContentSize(Size(2048, 2048));
    layer1->setPosition(w, h);
    
    layer2 = Sprite::create();
    layer2->setContentSize(Size(2048, 2048));
    layer2->setPosition(w, h);
    
    layer3 = Sprite::create();
    layer3->setContentSize(Size(2048, 2048));
    layer3->setPosition(w, h);
    
    layer4 = Sprite::create();
    layer4->setContentSize(Size(2048, 2048));
    layer4->setPosition(w, h);

    w = layer1->getContentSize().width / 2;
    h = layer1->getContentSize().height / 2;
    
	Sprite * earth1 = Sprite::createWithSpriteFrameName("earth-1.png");
	earth1->setAnchorPoint(Vec2(1, 0));
	earth1->setPosition(w, h);

	Sprite * earth2 = Sprite::createWithSpriteFrameName("earth-2.png");
	earth2->setAnchorPoint(Vec2(0, 0));
	earth2->setPosition(w, h);

	Sprite * earth3 = Sprite::createWithSpriteFrameName("earth-3.png");
	earth3->setAnchorPoint(Vec2(0, 1));
	earth3->setPosition(w, h);

	Sprite * earth4 = Sprite::createWithSpriteFrameName("earth-4.png");
	earth4->setAnchorPoint(Vec2(1, 1));
	earth4->setPosition(w, h);

 
    Sprite * rock1_1_1 = Sprite::createWithSpriteFrameName("rock1.png");
    rock1_1_1->setRotation(-45);
    rock1_1_1->setAnchorPoint(Vec2(0, 1));
    rock1_1_1->setPosition(221, 1570);
    
    Sprite * rock1_1_2 = Sprite::createWithSpriteFrameName("rock1.png");
    rock1_1_2->setRotation(62);
    rock1_1_2->setAnchorPoint(Vec2(0, 1));
    rock1_1_2->setPosition(1750, 1612);
    
    Sprite * rock1_1_3 = Sprite::createWithSpriteFrameName("rock1.png");
    rock1_1_3->setRotation(-154);
    rock1_1_3->setAnchorPoint(Vec2(0, 1));
    rock1_1_3->setPosition(1461, 268);
    
    Sprite * rock1_1_4 = Sprite::createWithSpriteFrameName("rock1.png");
    rock1_1_4->setRotation(-120);
    rock1_1_4->setAnchorPoint(Vec2(0, 1));
    rock1_1_4->setPosition(415, 314);

    Sprite * rock1_2_1 = Sprite::createWithSpriteFrameName("rock2.png");
    rock1_2_1->setRotation(90);
    rock1_2_1->setPosition(1816, 1317);
    rock1_2_1->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock1_2_2 = Sprite::createWithSpriteFrameName("rock2.png");
    rock1_2_2->setRotation(-148);
    rock1_2_2->setPosition(636, 260);
    rock1_2_2->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock1_2_3 = Sprite::createWithSpriteFrameName("rock2.png");
    rock1_2_3->setRotation(-50);
    rock1_2_3->setPosition(269, 1288);
    rock1_2_3->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_1_1 = Sprite::createWithSpriteFrameName("plant1.png");
    plant2_1_1->setRotation(-18);
    plant2_1_1->setPosition(702, 1833);
    plant2_1_1->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_1_2 = Sprite::createWithSpriteFrameName("plant1.png");
    plant2_1_2->setRotation(35);
    plant2_1_2->setPosition(1447, 1743);
    plant2_1_2->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_1_3 = Sprite::createWithSpriteFrameName("plant1.png");
    plant2_1_3->setRotation(131);
    plant2_1_3->setPosition(1711, 511);
    plant2_1_3->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_1_4 = Sprite::createWithSpriteFrameName("plant1.png");
    plant2_1_4->setRotation(-134);
    plant2_1_4->setPosition(407, 467);
    plant2_1_4->setAnchorPoint(Vec2(0, 1));
    
    
    Sprite * plant2_2_1 = Sprite::createWithSpriteFrameName("plant2.png");
    plant2_2_1->setRotation(-8);
    plant2_2_1->setPosition(916, 1784);
    plant2_2_1->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_2_2 = Sprite::createWithSpriteFrameName("plant2.png");
    plant2_2_2->setRotation(50);
    plant2_2_2->setPosition(1573, 1506);
    plant2_2_2->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_2_3 = Sprite::createWithSpriteFrameName("plant2.png");
    plant2_2_3->setRotation(165);
    plant2_2_3->setPosition(1179, 280);
    plant2_2_3->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_2_4 = Sprite::createWithSpriteFrameName("plant2.png");
    plant2_2_4->setRotation(-152);
    plant2_2_4->setPosition(731, 332);
    plant2_2_4->setAnchorPoint(Vec2(0, 1));
    
    Sprite * plant2_2_5 = Sprite::createWithSpriteFrameName("plant2.png");
    plant2_2_5->setRotation(-73);
    plant2_2_5->setPosition(289, 1003);
    plant2_2_5->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock3_1_1 = Sprite::createWithSpriteFrameName("rock4.png");
    rock3_1_1->setRotation(-17);
    rock3_1_1->setPosition(441, 1694);
    rock3_1_1->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock3_1_2 = Sprite::createWithSpriteFrameName("rock4.png");
    rock3_1_2->setRotation(109);
    rock3_1_2->setPosition(1858, 1135);
    rock3_1_2->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock3_1_3 = Sprite::createWithSpriteFrameName("rock4.png");
    rock3_1_3->setRotation(-160);
    rock3_1_3->setPosition(1301, 137);
    rock3_1_3->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock3_2_1 = Sprite::createWithSpriteFrameName("rock3.png");
    rock3_2_1->setRotation(-72);
    rock3_2_1->setPosition(214, 975);
    rock3_2_1->setAnchorPoint(Vec2(0, 1));
    
    Sprite * rock3_2_2 = Sprite::createWithSpriteFrameName("rock3.png");
    rock3_2_2->setRotation(135);
    rock3_2_2->setPosition(1761, 701);
    rock3_2_2->setAnchorPoint(Vec2(0, 1));

    
    layer1->addChild(earth1);
    layer1->addChild(earth2);
    layer1->addChild(earth3);
    layer1->addChild(earth4);
    layer2->addChild(rock1_1_1);
    layer2->addChild(rock1_1_2);
    layer2->addChild(rock1_1_3);
    layer2->addChild(rock1_1_4);
    layer2->addChild(rock1_2_1);
    layer2->addChild(rock1_2_2);
    layer2->addChild(rock1_2_3);
    layer3->addChild(plant2_1_1);
    layer3->addChild(plant2_1_2);
    layer3->addChild(plant2_1_3);
    layer3->addChild(plant2_1_4);
    layer3->addChild(plant2_2_1);
    layer3->addChild(plant2_2_2);
    layer3->addChild(plant2_2_3);
    layer3->addChild(plant2_2_4);
    layer3->addChild(plant2_2_5);
    layer4->addChild(rock3_1_1);
    layer4->addChild(rock3_1_2);
    layer4->addChild(rock3_1_3);
    layer4->addChild(rock3_2_1);
    layer4->addChild(rock3_2_2);
    this->addChild(layer1, 4);
    this->addChild(layer2, 3);
    this->addChild(layer3, 2);
    this->addChild(layer4, 1);
    

    
    Ore* itemA1 = new Ore("item_a_1.png", 100, 150, 20, 3);
	itemA1->setOpacity(0);
	itemA1->setTag(10);
	layer4->addChild(itemA1);
	itemArr.pushBack(itemA1);
    
	Ore* itemA2 = new Ore("item_a_2.png", 400, 80, 30, 4);
	itemA2->setOpacity(0);
	itemA2->setTag(11);
	layer4->addChild(itemA2);
	itemArr.pushBack(itemA2);
    
	Ore* itemA3 = new Ore("item_a_3.png", 500, 140, 50, 5);
	itemA3->setOpacity(0);
	itemA3->setTag(12);
	layer4->addChild(itemA3);
	itemArr.pushBack(itemA3);
    
    
	Ore* itemB1 = new Ore("item_b_1.png", 300, 50, 30, 4);
	itemB1->setOpacity(0);
	itemB1->setTag(13);
	layer4->addChild(itemB1);
	itemArr.pushBack(itemB1);
    
	Ore* itemB2 = new Ore("item_b_2.png", 300, 180, 40, 5);
	itemB2->setOpacity(0);
	itemB2->setTag(14);
	layer4->addChild(itemB2);
	itemArr.pushBack(itemB2);
    
	Ore* itemB3 = new Ore("item_b_3.png", 720, 200, 50, 6);
	itemB3->setOpacity(0);
	itemB3->setTag(15);
	layer4->addChild(itemB3);
	itemArr.pushBack(itemB3);
    
	Ore* itemC1 = new Ore("item_c_1.png", 1100, 10, 20, 3);
	itemC1->setOpacity(0);
	itemC1->setTag(16);
	layer4->addChild(itemC1);
	itemArr.pushBack(itemC1);
    
	Ore* itemC2 = new Ore("item_c_2.png", 970, 180, 30, 4);
	itemC2->setOpacity(0);
	itemC2->setTag(17);
	layer4->addChild(itemC2);
	itemArr.pushBack(itemC2);
    
	Ore* itemC3 = new Ore("item_c_3.png", 900, 140, 40, 5);
	itemC3->setOpacity(0);
	itemC3->setTag(18);
	layer4->addChild(itemC3);
	itemArr.pushBack(itemC3);

	return true;
}


void Earth::showOre(){
    for(Ore* item : itemArr){
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *itemA1FadeIn = FadeIn::create(time);
		item->runAction(itemA1FadeIn);
	}
}

void Earth::startTurn(){
    layer1->runAction(RepeatForever::create(RotateBy::create(5.0f,45)));
    layer2->runAction(RepeatForever::create(RotateBy::create(6.0f,45)));
    layer3->runAction(RepeatForever::create(RotateBy::create(7.0f,45)));
    layer4->runAction(RepeatForever::create(RotateBy::create(8.0f,45)));
    
    for(Ore* item : itemArr){
		item->changeToNormalBody();
	}
}


void Earth::stopTurn() {
    this->stopAllActions();
    
    for(Ore* item : itemArr){
		item->changeToPhysicsBody();
	}
}
