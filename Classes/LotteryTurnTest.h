#ifndef _LOTTERY_TURN_TEST_H_
#define _LOTTERY_TURN_TEST_H_

#include "cocos2d.h"

USING_NS_CC;

class LotteryTurnTest : public cocos2d::Layer
{
public:
	LotteryTurnTest();
	~LotteryTurnTest();

	static cocos2d::Scene * create();
	virtual bool init();

protected:
	void onBtnCallback(Ref * obj);
	void onTurnEnd();
private:
	Sprite * m_turnBg;
	MenuItemSprite * m_turnArr;
	Sprite * m_pBg;
	ParticleSystemQuad * m_pElliRtt_1;
	ParticleSystemQuad * m_pElliRtt_2;
	ParticleSystemQuad * m_pCircle_1;
	ParticleSystemQuad * m_pCircle_2;
};

#endif