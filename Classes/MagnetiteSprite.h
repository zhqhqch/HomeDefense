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

class Magnetite : public cocos2d::Sprite {
public:
    Magnetite(GameView *gw, float x, float y);
    
    //将磁铁石伸出飞船
    void reach();
    
    //磁铁石是否在移动
    bool isMove(){return move;};
    
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
