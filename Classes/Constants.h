//
//  Constants.h
//  HomeDefense
//
//  Created by huqichao on 15-1-15.
//
//

#ifndef HomeDefense_Constants_h
#define HomeDefense_Constants_h

#define kPintNull Point(9999,9999)

#define kEarthZOrder 50
#define kGameUIZOrder 60
#define kAirShipZOrder 70
#define kMagnetiteZOrder 80

#define kWallTag 99

#define kLightLineTag 100

#define kOreTag 1000

#define kOrePitWithOreTag 1000 // 矿石坑与矿石tag之间相差的值

#define kMagnetiteFinishMove_Sway 1
#define kMagnetiteFinishMove_Back 2

#define kMoveBackTime 3.0f


#define kSpeedProp 1
#define kBombProp 2
#define kTimeProp 3

//显示矿石层级
#define kInnterType 1	//内层
#define kMiddleType 2	//中层
#define kOuterType 3	//外层

//矿石坑落石动画
#define pitFallenRockAnimationName "pitFallenRock"
#define pitFallenRockAnimationPrefixStr "pit"
#define pitFallenRockAnimationCount 9

//抓取失败动画
#define catchFailAnimationName "catchFail"
#define catchFailAnimationPrefixStr "player-cry"
#define catchFailAnimationCount 2

//抓取成功动画
#define catchSuccessAnimationName "catchSuccess"
#define catchSuccessAnimationPrefixStr "player-happy"
#define catchSuccessAnimationCount 2

#endif
