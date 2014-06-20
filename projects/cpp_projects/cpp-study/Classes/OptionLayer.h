//
//  OptionLayer.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#ifndef __cpp_study__OptionLayer__
#define __cpp_study__OptionLayer__

#include <cocos2d.h>
#include <OptionDelegate.h>


class OptionLayer : public cocos2d::Layer
{
public:
    OptionLayer();
    ~OptionLayer();
    
    virtual bool init();
    
    CREATE_FUNC(OptionLayer);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
    
    
    CC_SYNTHESIZE(OptionDelegate*, _delegator, Delegator);
    
private:
    
    cocos2d::Sprite *_joystick;
    cocos2d::Sprite *_joystick_bg;
    
    void _activityJoystick(cocos2d::Point position);
    
    void _inactivityJoystick();
    
    void _updateJoystick(cocos2d::Point direction, float distance);
    
};

#endif /* defined(__cpp_study__OptionLayer__) */
