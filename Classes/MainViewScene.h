#ifndef __MAINVIEW_SCENE_H__
#define __MAINVIEW_SCENE_H__

#include "cocos2d.h"

class MainView : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void menuShareCallback(cocos2d::Ref* pSender);

    void menuShopCallback(cocos2d::Ref* pSender);

    void menuStartCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainView);
};

#endif // __MAINVIEW_SCENE_H__
