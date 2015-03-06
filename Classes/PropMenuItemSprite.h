//
//  PropMenuItemSprite.h
//  HomeDefense
//
//  Created by huqichao on 15-3-6.
//
//

#ifndef __HomeDefense__PropMenuItemSprite__
#define __HomeDefense__PropMenuItemSprite__

#include "cocos2d.h"

class PropSprite : public cocos2d::MenuItemSprite {
public:
    PropSprite(int pID, int count, const std::string& imageName);
    
private:
    int propID;
    int propCount;
    
    cocos2d::Label *countLable;
    
    //使用道具
    void useProp();
};


#endif /* defined(__HomeDefense__PropMenuItemSprite__) */
