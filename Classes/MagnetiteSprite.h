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
    Magnetite(GameView *gw, float x, float y);
    
    //将磁铁石伸出飞船
    void reach();
    
    //磁铁石是否在移动
    bool isMove(){return move;}

    bool isReach(){return reachRope;}
    bool isBack(){return backRope;}
    
    //开始跟随绳子摆动
    void startFollow(cocos2d::Point point);
    
    //移动到指定点
    void moveToPoint(cocos2d::Point curPoint, cocos2d::Point targetPoint);
    //回到起点
    void backWithOreToStartPoint();

    //回到起点
    void backToStartPoint();
    
    //停止移动，将Velocity设置为0
    void stopMove();
    
    void show();
    void hide();

    cocos2d::Point getStartPoint(){return startPoint;}
private:
    bool move;
    bool showScore;
    bool reachRope;
    bool backRope;
    GameView *gameView;
    cocos2d::Point startPoint;
    cocos2d::Vec2 moveVelocity;
    
    //结束移动
    void finishMove(int nextActionType);
    
    //磁铁石准备左右摇摆
    void readySway();
    
};

#endif
