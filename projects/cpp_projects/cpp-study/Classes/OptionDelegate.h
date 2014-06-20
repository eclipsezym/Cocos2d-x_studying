//
//  OptionDelegate.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-21.
//
//

#ifndef __cpp_study__OptionDelegate__
#define __cpp_study__OptionDelegate__

#include <cocos2d.h>

class OptionDelegate
{
public:
    
    virtual void onWalk(cocos2d::Point direction, float distance) = 0;
    
    virtual void onAttack() = 0;
    
    virtual void onStop() = 0;
};

#endif /* defined(__cpp_study__OptionDelegate__) */
