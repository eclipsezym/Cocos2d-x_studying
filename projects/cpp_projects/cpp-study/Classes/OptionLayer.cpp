//
//  OptionLayer.cpp
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#include "OptionLayer.h"
using namespace cocos2d;
using namespace std;


OptionLayer::OptionLayer(){}

OptionLayer::~OptionLayer(){}

bool OptionLayer::init()
{
    bool ret = false;
    
    do{
        CC_BREAK_IF(!Layer::init());
        
        _joystick = Sprite::create("pd_dpad.png");
        
        _joystick_bg = Sprite::create("pd_dpad-hd.png");
        
        this->addChild(_joystick_bg);
        this->addChild(_joystick);
      
        
//        setTouchEnabled(true);
        
        EventDispatcher *dispatcher = Director::getInstance()->getEventDispatcher();
        EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(OptionLayer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(OptionLayer::onTouchesEnded, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        ret = true;
        
    }while (0);
    
    return ret;
}

void OptionLayer::_activityJoystick(Point position)
{
    _joystick->setPosition(position);
    _joystick_bg->setPosition(position);
    _joystick->setVisible(true);
    _joystick_bg->setVisible(true);
    
}

void OptionLayer::_inactivityJoystick()
{
    _joystick->setPosition(_joystick_bg->getPosition());
    _joystick->setVisible(false);
    _joystick_bg->setVisible(false);
}

void OptionLayer::_updateJoystick(Point direction, float distance)
{
    Point start = _joystick_bg->getPosition();
    
    if (distance < 32) {
        _joystick->setPosition(start + (direction * distance));
    }else if (distance > 96){
        _joystick->setPosition(start + (direction * 64));
    }else{
        _joystick->setPosition(start + (direction * 32));
    }

}


void OptionLayer::onTouchesBegan(const vector<Touch *> &touches, Event *unused_event)
{
    Size winSize = Director::getInstance()->getWinSize();
    auto item = touches.begin();
    while (item != touches.end()) {
        Touch *t = (Touch*)(*item);
        Point p = t->getLocation();
        
        if (p.x <= winSize.width / 2) {
            _activityJoystick(p);
        }else{
            _delegator->onAttack();
        }
        item++;
    
    }
    
}

void OptionLayer::onTouchesMoved(const vector<Touch *> &touches, Event *unused_event)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    auto item = touches.begin();
    Touch *t = (Touch*)(*item);
    Point start = t->getStartLocation();
    
    if (start.x > winSize.width / 2) {
        return;
    }
    
    Point p =  t->getLocation();
    
    float distance = start.getDistance(p);
    
    Point direction = (p - start).getNormalized();
    
    _updateJoystick(direction, distance);
    
    _delegator->onWalk(direction, distance);
}

void OptionLayer::onTouchesEnded(const vector<Touch *> &touches, Event *unused_event)
{
    _inactivityJoystick();
    
    _delegator->onStop();
}















