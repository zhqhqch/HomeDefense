#include "MainViewScene.h"

USING_NS_CC;

Scene* MainView::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainView::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainView::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto airshipSprite = Sprite::create("airship.png");
    airshipSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.7));
    this->addChild(airshipSprite, 1);


    auto startItem = MenuItemImage::create(
                                           "startBtn.png",
                                           "startBtn_selected.png",
                                           CC_CALLBACK_1(MainView::menuCloseCallback, this));
    
    startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));

    auto shareItem = MenuItemImage::create("shareBtn.png",
    										"shareBtn_selected.png",
    										CC_CALLBACK_1(MainView::menuShareCallback, this));

    shareItem->setPosition(Vec2(shareItem->getContentSize().width / 2,
    						shareItem->getContentSize().height / 2));

    auto shopItem = MenuItemImage::create("shopBtn.png",
        										"shopBtn_selected.png",
        										CC_CALLBACK_1(MainView::menuShopCallback, this));

    shopItem->setPosition(Vec2(visibleSize.width - shopItem->getContentSize().width / 2,
    						shopItem->getContentSize().height / 2));

    auto menu = Menu::create(startItem,shareItem, shopItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto mainBgSprite = Sprite::create("main_bg.jpg");
    mainBgSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float scale_x = visibleSize.width / mainBgSprite->getContentSize().width;
    float scale_y = visibleSize.height / mainBgSprite->getContentSize().height;
    if(scale_x > scale_y){
    	mainBgSprite->setScale(scale_x);
    } else {
    	mainBgSprite->setScale(scale_y);
    }

    this->addChild(mainBgSprite, 0);
    
    return true;
}


void MainView::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainView::menuShareCallback(Ref* pSender) {


}


void MainView::menuShopCallback(Ref* pSender) {


}