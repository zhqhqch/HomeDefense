#include "LotteryTurnTest.h"
#include "EllipseBy.h"

LotteryTurnTest::LotteryTurnTest()
: m_turnBg(nullptr)
, m_turnArr(nullptr)
, m_pBg(nullptr)
, m_pElliRtt_1(nullptr)
, m_pElliRtt_2(nullptr)
, m_pCircle_1(nullptr)
, m_pCircle_2(nullptr)
{

}

LotteryTurnTest::~LotteryTurnTest()
{

}

Scene * LotteryTurnTest::create()
{
	auto scene = Scene::create();
	auto pLayer = new LotteryTurnTest();
	if (pLayer && pLayer->init())
	{
		pLayer->autorelease();
		scene->addChild(pLayer);
		return scene;
	}
	else
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
}

bool LotteryTurnTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bgSize = Director::getInstance()->getWinSize();

	m_pBg = Sprite::create("LotteryTurn/bg_big.png");
	m_pBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
	this->addChild(m_pBg);

	//添加标题
	auto plabel = Label::createWithTTF("LotteryTurnTest","fonts/Marker Felt.ttf",30);
	plabel->setPosition(Vec2(bgSize.width / 2,bgSize.height * 0.9));
	m_pBg->addChild(plabel);

	//添加转盘
	m_turnBg = Sprite::create("LotteryTurn/turn_bg.png");
	m_turnBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
	m_pBg->addChild(m_turnBg);

	//添加指针
	auto arrNor = Sprite::create("LotteryTurn/turn_arrow.png");
	auto arrSel = Sprite::create("LotteryTurn/turn_arrow.png");
	arrSel->setColor(Color3B(190,190,190));
	m_turnArr = MenuItemSprite::create(arrNor,arrSel,CC_CALLBACK_1(LotteryTurnTest::onBtnCallback,this));
	m_turnArr->setPosition(Vec2(bgSize.width / 2,bgSize.height * 0.557));
	m_turnArr->setScale(0.7);
	auto pMenu = Menu::createWithItem(m_turnArr);
	pMenu->setPosition(Vec2::ZERO);
	m_pBg->addChild(pMenu);

	//添加中奖之后的简单界面
	auto awardLayer = LayerColor::create(Color4B(0,0,0,100));
	awardLayer->setPosition(Point::ZERO);
	awardLayer->setTag(100);
	m_pBg->addChild(awardLayer,10);
	awardLayer->setVisible(false);

	return true;
}

void LotteryTurnTest::onBtnCallback(Ref * obj)
{
	//防止多次点击
	m_turnArr->setEnabled(false);

	srand(unsigned(time(NULL)));
	float angleZ = rand() % 720 + 720;
	auto pAction = EaseExponentialOut::create(RotateBy::create(4,Vec3(0,0,angleZ)));
	m_turnBg->runAction(Sequence::create(pAction,CallFunc::create(CC_CALLBACK_0(LotteryTurnTest::onTurnEnd,this)),NULL));

	//添加椭圆旋转粒子效果
	m_pElliRtt_1 = ParticleSystemQuad::create("LotteryTurn/whiteBall.plist");
	m_pBg->addChild(m_pElliRtt_1);
	m_pElliRtt_2 = ParticleSystemQuad::create("LotteryTurn/yellowBall.plist");
	m_pBg->addChild(m_pElliRtt_2);

	//椭圆旋转
	EllipseConfig config;
	config.ellipseA = 100;
	config.ellipseB = 50;
	config.cenPos = m_turnBg->getPosition();
	config.isAntiClockwise = true;
	config.startAngle = 0;
	config.selfAngle = 45;

	m_pElliRtt_1->runAction(RepeatForever::create( EllipseBy::create(2.5,config)));

	config.startAngle = 180;
	config.selfAngle = -45;

	m_pElliRtt_2->runAction(RepeatForever::create(EllipseBy::create(2.5,config)));

	//圈圈闪烁粒子效果
	m_pCircle_1 = ParticleSystemQuad::create("LotteryTurn/bigCircle.plist");
	m_pCircle_1->setPosition(m_turnBg->getPosition());
	m_pBg->addChild(m_pCircle_1);
	m_pCircle_1->runAction(RepeatForever::create(RotateBy::create(5,Vec3(0,0,angleZ))));

	m_pCircle_2 = ParticleSystemQuad::create("LotteryTurn/smallCircle.plist");
	m_pCircle_2->setPosition(m_turnBg->getPosition());
	m_pBg->addChild(m_pCircle_2);
	m_pCircle_2->runAction(RepeatForever::create(RotateBy::create(5,Vec3(0,0,angleZ))));

}

void LotteryTurnTest::onTurnEnd()
{
	m_pElliRtt_1->removeFromParentAndCleanup(true);
	m_pElliRtt_2->removeFromParentAndCleanup(true);
	m_pCircle_1->removeFromParentAndCleanup(true);
	m_pCircle_2->removeFromParentAndCleanup(true);
	
	//弹出抽中奖品
	((LayerColor *)m_pBg->getChildByTag(100))->setVisible(true);
	auto award = Sprite::create("LotteryTurn/award.png");
	award->setAnchorPoint(Vec2(0.5,0));
	award->setPosition(Vec2(m_pBg->getPositionX(),m_pBg->getPositionY() * 2));
	this->addChild(award);
	auto bounce = EaseBounceOut::create(MoveBy::create(2,Vec2(0,-m_pBg->getPositionX() * 2)));
	award->runAction(Sequence::createWithTwoActions(bounce,CallFuncN::create([=](Node * node){
					award->removeFromParentAndCleanup(true);
					((LayerColor *)m_pBg->getChildByTag(100))->setVisible(false);
					m_turnArr->setEnabled(true);
	})));

}