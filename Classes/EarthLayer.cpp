/*
 * EarthLayer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: hqch
 */

#include "EarthLayer.h"
#include "Constants.h"
#include "Util.h"
#include "GameViewScene.h"

USING_NS_CC;


Earth::Earth(GameView * gw, Checkpoint *c){
	checkpoint = c;
	gameView = gw;
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
    
	Sprite * earth1 = Sprite::create("checkpoint1-earth-1.png");
	earth1->setAnchorPoint(Vec2(1, 0));
	earth1->setPosition(w, h);

	Sprite * earth2 = Sprite::create("checkpoint1-earth-2.png");
	earth2->setAnchorPoint(Vec2(0, 0));
	earth2->setPosition(w, h);

	Sprite * earth3 = Sprite::create("checkpoint1-earth-3.png");
	earth3->setAnchorPoint(Vec2(0, 1));
	earth3->setPosition(w, h);

	Sprite * earth4 = Sprite::create("checkpoint1-earth-4.png");
	earth4->setAnchorPoint(Vec2(1, 1));
	earth4->setPosition(w, h);
    
    layer1->addChild(earth1);
    layer1->addChild(earth2);
    layer1->addChild(earth3);
    layer1->addChild(earth4);


	Vector<Checkpoint::BgData *> bgArr = checkpoint->bgArray;
	for(Checkpoint::BgData * bgData : bgArr){
		Sprite * sprite = Sprite::createWithSpriteFrameName(bgData->imageName);
		sprite->setRotation(bgData->rotation);
		sprite->setAnchorPoint(Vec2(0, 1));
		sprite->setPosition(bgData->positionX, bgData->positionY);

		if(bgData->layerNum == 2){
			layer2->addChild(sprite);
		} else if(bgData->layerNum == 3){
			layer3->addChild(sprite);
		} else if(bgData->layerNum == 4){
			layer4->addChild(sprite);
		}
	}


    this->addChild(layer1, 4);
    this->addChild(layer2, 2);
    this->addChild(layer3, 3);
    this->addChild(layer4, 1);
    

    int tag = 10;
    Vector<Checkpoint::RockData *> innterRockArr = checkpoint->getShowRockByType(kInnterType);
    initOre(innterRockArr, tag);

    tag += innterRockArr.size();
    Vector<Checkpoint::RockData *> middleRockArr = checkpoint->getShowRockByType(kMiddleType);
    initOre(middleRockArr, tag);

    tag += middleRockArr.size();
	Vector<Checkpoint::RockData *> outerRockArr = checkpoint->getShowRockByType(kOuterType);
	initOre(outerRockArr, tag);
	return true;
}

void Earth::initOre(Vector<Checkpoint::RockData *> rockArr, int tag){
	for(Checkpoint::RockData *rock : rockArr){
		Array * strs = Util::split(rock->imageName.c_str(), "-");
		char imageName[50];
		sprintf(imageName, "Checkpoint1-pit-%s", static_cast<String*>(strs->objectAtIndex(2))->_string.c_str());
		OrePit* orePit = new OrePit(imageName, rock->positionX, rock->positionY,
				 rock->rotation);
		orePit->setOpacity(0);
		layer1->addChild(orePit);
		orePitArr.pushBack(orePit);

		Ore* ore = new Ore(rock->imageName, rock->positionX, rock->positionY,
				 rock->rotation, rock->score, rock->weight);
		ore->setOpacity(0);
		ore->setTag(tag ++);
		layer1->addChild(ore);
		oreArr.pushBack(ore);
	}
}

void Earth::showOre(){
	for(int i = 0; i < oreArr.size(); i++){
		OrePit* orepit = orePitArr.at(i);
		float time = CCRANDOM_0_1() * 3 + 0.5f;
		FadeIn *orePitFadeIn = FadeIn::create(time);
		orepit->runAction(orePitFadeIn);

		Ore* ore = oreArr.at(i);
		FadeIn *oreFadeIn = FadeIn::create(time);
		ore->runAction(oreFadeIn);
	}
}

void Earth::startTurn(){
    layer1->runAction(RepeatForever::create(RotateBy::create(checkpoint->layer1Speed,45)));
    layer2->runAction(RepeatForever::create(RotateBy::create(checkpoint->layer2Speed,45)));
    layer3->runAction(RepeatForever::create(RotateBy::create(checkpoint->layer3Speed,45)));
    layer4->runAction(RepeatForever::create(RotateBy::create(checkpoint->layer4Speed,45)));
    
    for(Ore* item : oreArr){
		item->changeToNormalBody();
//		item->changeToPhysicsBody();
	}

}


void Earth::stopTurn() {
    this->stopAllActions();
    
    for(Ore* item : oreArr){
		item->changeToPhysicsBody();
	}
}

bool Earth::isCatchOre(Point point, float r) {
	Point tmp = layer1->convertToNodeSpace(point);
	for(Ore * ore : oreArr){
		//计算圆心距离
		float dist = ore->getPosition().getDistance(tmp);
		isCatch = dist < (ore->getContentSize().width / 2 + r);
		if(isCatch){
			catchOre = ore;
			gameView->catchOreToAirShip(ore);
			ore->removeFromParentAndCleanup(true);
			oreArr.eraseObject(ore);
			return isCatch;
		}
	}

	return false;
}

void Earth::catchOreToAirShip(Point position) {
	Point tmp = layer1->convertToNodeSpace(position);
	MoveTo * moveTo = MoveTo::create(5.0, tmp);
	CallFunc *fun = CallFunc::create(CC_CALLBACK_0(Earth::finishCatch, this));
	Sequence * seq = Sequence::create(moveTo, fun, NULL);
	catchOre->runAction(seq);
}

void Earth::finishCatch(){
//	gameView->catchBack(catchOre);

	catchOre->removeFromParentAndCleanup(true);
	oreArr.eraseObject(catchOre);
}
