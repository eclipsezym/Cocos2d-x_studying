//
//  NoTouchLayer.h
//  DemonDefence
//
//  Created by 韩 剑伟 on 13-9-2.
//
//

#ifndef __DemonDefence__NoTouchLayer__
#define __DemonDefence__NoTouchLayer__

#include "cocos2d.h"
USING_NS_CC;

class NoTouchLayer : public Layer{
public:
    virtual bool init();
    
    CREATE_FUNC(NoTouchLayer);
    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan (Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved (Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded (Touch *pTouch, Event *pEvent);
    
};

#endif /* defined(__DemonDefence__NoTouchLayer__) */
