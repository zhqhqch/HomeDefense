//
//  PropMenuItemSprite.cpp
//  HomeDefense
//
//  Created by huqichao on 15-3-6.
//
//

#include "PropMenuItemSprite.h"


USING_NS_CC;

PropSprite::PropSprite(int pID, int count, const std::string& imageName){
    propID = pID;
    propCount = count;
    
    std::string normal,selected, disabled;
    
    normal = imageName + ".png";
    selected = imageName + "-selected.png";
    disabled = imageName + "-disabled.png";
    
    MenuItemSprite::initWithNormalSprite(Sprite::createWithSpriteFrameName(normal),
                                         Sprite::createWithSpriteFrameName(selected),
                                         Sprite::createWithSpriteFrameName(disabled),
                                         CC_CALLBACK_0(PropSprite::useProp, this));
    
    auto speedNumSprite = Sprite::createWithSpriteFrameName("number-bg.png");
    speedNumSprite->setPosition(speedNumSprite->getContentSize().width / 2,
                                getContentSize().height - speedNumSprite->getContentSize().height / 2);
    this->addChild(speedNumSprite);
    
    char a[3];
    sprintf(a,"%d",count);
    
    countLable = Label::create();
	countLable->setString(a);
	countLable->setSystemFontSize(25);
    countLable->setPosition(speedNumSprite->getContentSize().width / 2, speedNumSprite->getContentSize().height / 2);
    
    speedNumSprite->addChild(countLable);

    if(count <= 0){
    	setEnabled(false);
    }
}


void PropSprite::useProp() {
    if (propCount <= 0) {
        log("prop not enough.id=%d, count=%d", propID, propCount);
        return;
    }
    
    propCount--;
    
    char a[3];
    sprintf(a,"%d",propCount);
    countLable->setString(a);
    log("useprop***********************%d", propID);
    
    if(propCount <= 0){
        setEnabled(false);
    }
}
