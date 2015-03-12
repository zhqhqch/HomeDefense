#include "MainViewScene.h"
#include "TransitionUtil.h"
#include "GameViewScene.h"
#include "base/ZipUtils.h"

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
    
    
    //设置纹理解密key83a16bbf7480499fc4fc4c6349a381b8
    ZipUtils::setPvrEncryptionKeyPart(0, 0x83a16bbf);
    ZipUtils::setPvrEncryptionKeyPart(1, 0x7480499f);
    ZipUtils::setPvrEncryptionKeyPart(2, 0xc4fc4c63);
    ZipUtils::setPvrEncryptionKeyPart(3, 0x49a381b8);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto airshipSprite = Sprite::create("airship.png");
    airshipSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.7));
    this->addChild(airshipSprite, 1);


    auto startItem = MenuItemImage::create(
                                           "startBtn.png",
                                           "startBtn_selected.png",
                                           CC_CALLBACK_1(MainView::menuStartCallback, this));
    
    startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));

    
    auto shareItem = MenuItemImage::create("shareBtn.png",
    										"shareBtn_selected.png",
    										CC_CALLBACK_1(MainView::menuShareCallback, this));

    shareItem->setPosition(Vec2(shareItem->getContentSize().width / 2 + 38,
    						shareItem->getContentSize().height / 2 + 33));

    
    auto shopItem = MenuItemImage::create("shopBtn.png",
        										"shopBtn_selected.png",
        										CC_CALLBACK_1(MainView::menuShopCallback, this));

    shopItem->setPosition(Vec2(visibleSize.width - shopItem->getContentSize().width / 2 - 38,
    						shopItem->getContentSize().height / 2 + 33));
    
    auto menu = Menu::create(startItem,shareItem, shopItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto mainBgSprite = Sprite::create("main_bg.jpg");
    mainBgSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    this->addChild(mainBgSprite, 0);
    
    ParticleSystem * ps = ParticleSnow::create();
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("item_a_1.png"));
    ps->setPosition(visibleSize.width / 2,visibleSize.height * 0.9);
    this->addChild(ps, 2);

    return true;
}

void MainView::menuStartCallback(Ref* pSender) {
//	auto gameView = GameViewOld::createScene();
	auto gameView = GameView::createScene();
	TransitionUtil::enterScene(gameView);
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void MainView::menuShopCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
