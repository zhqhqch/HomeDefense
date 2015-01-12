/*
 * TransitionUtil.cpp
 *
 *  Created on: 2015年1月12日
 *      Author: hqch
 */

#include "TransitionUtil.h"

USING_NS_CC;

#define kTransitionTime 1.0f

//进入场景过渡动画
void TransitionUtil::enterScene(cocos2d::Scene * targetScene){
	TransitionScene *scene = TransitionMoveInR::create(kTransitionTime, targetScene);
	Director::getInstance()->replaceScene(scene);
}


//退出场景过渡动画
void TransitionUtil::backScene(cocos2d::Scene * targetScene){
	TransitionScene *scene = TransitionMoveInL::create(kTransitionTime, targetScene);
	Director::getInstance()->replaceScene(scene);
}
