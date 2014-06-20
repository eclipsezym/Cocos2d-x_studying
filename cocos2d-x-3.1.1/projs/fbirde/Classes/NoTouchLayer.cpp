//
//  NoTouchLayer.cpp
//  DemonDefence
//
//  Created by 韩 剑伟 on 13-9-2.
//
//

#include "NoTouchLayer.h"

bool NoTouchLayer::init(){
    if (!CCLayer::init() )
    {
        return false;
    }
    
    setTouchEnabled(true);
    
    return true;
}

void NoTouchLayer::registerWithTouchDispatcher(){
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, -100000, true);//使用int最小值做最高优先级,并且吞掉事件true
    CCLayer::registerWithTouchDispatcher();
}

bool NoTouchLayer::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent){
    return true;
}

void NoTouchLayer::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent){
}


void NoTouchLayer::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent){
}



