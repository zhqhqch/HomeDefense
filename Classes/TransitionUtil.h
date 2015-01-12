/*
 * TransitionUtil.h
 *
 *  Created on: 2015年1月12日
 *      Author: hqch
 */

#ifndef TRANSITIONUTIL_H_
#define TRANSITIONUTIL_H_

#include "cocos2d.h"

class TransitionUtil {

public:
	static void enterScene(cocos2d::Scene * targetScene);
	static void backScene(cocos2d::Scene * targetScene);
};


#endif /* TRANSITIONUTIL_H_ */
