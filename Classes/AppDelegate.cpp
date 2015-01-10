#include "AppDelegate.h"
#include "MainViewScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");

        Size referenceSize = Size(1280,640);
        Size winSize = glview->getFrameSize();
        float scale_x = winSize.width / referenceSize.width;
        float scale_y = winSize.height / referenceSize.height;
        Size resolutionSize;
        if(scale_x < scale_y){
        	resolutionSize = Size(referenceSize.width, winSize.height / scale_x);
        } else {
        	resolutionSize = Size(winSize.width / scale_y, referenceSize.height);
        }
        glview->setDesignResolutionSize(resolutionSize.width,resolutionSize.height, kResolutionShowAll);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainView::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
