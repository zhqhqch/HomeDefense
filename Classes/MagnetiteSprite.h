//
//  MagnetiteSprite.h
//  HomeDefense
//
//  Created by huqichao on 15-1-16.
//
//

#ifndef HomeDefense_MagnetiteSprite_h
#define HomeDefense_MagnetiteSprite_h


#include "cocos2d.h"

class GameView;
class AirShipRope;

class Magnetite : public cocos2d::Sprite {
public:
    Magnetite(GameView *gw, cocos2d::Sprite * rope, float x, float y);
    
    //将磁铁石伸出飞船
    void reach();
    
    //磁铁石是否在移动
    bool isMove(){return move;};
    
    //开始跟随绳子摆动
    void startFollow();
    
    //停止跟随绳子摆动
    void stopFollow();
    
private:
    cocos2d::Sprite * ropeSprite;
    float startX;
    float startY;
    bool move;
    GameView *gameView;
    
    //结束移动
    void finishMove();
    
    //磁铁石准备左右摇摆
    void readySway();
};

#endif
