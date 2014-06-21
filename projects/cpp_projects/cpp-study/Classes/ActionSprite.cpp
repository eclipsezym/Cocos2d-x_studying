//
//  ActionSprite.cpp
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#include "ActionSprite.h"
using namespace cocos2d;

ActionSprite::ActionSprite()
{
    _idleAction = NULL;
    _walkAction = NULL;
    _attackAction = NULL;
    _hurtAction = NULL;
    _knockoutAction = NULL;
}

ActionSprite::~ActionSprite(){}

void ActionSprite::idle()
{
    if (_changeState(ACTION_STATE_IDLE)) {
        runAction(_idleAction);
        _velocity = 0;
    }
}

void ActionSprite::attack()
{
    if (_changeState(ACTION_STATE_ATTACK)) {
        runAction(_attackAction);
    }
}

void ActionSprite::walk()
{
    
    if (_changeState(ACTION_STATE_WALK)) {
        runAction(_walkAction);
    }
}

void ActionSprite::hurt()
{
    if (_changeState(ACTION_STATE_HURT)) {
        runAction(_hurtAction);
    }
    
}

void ActionSprite::knockout()
{
    if (_changeState(ACTION_STATE_KNOCKOUT)) {
        runAction(_knockoutAction);
    }
}

bool ActionSprite::_changeState(ActionState state)
{
    bool ret = false;
    
    //精靈已經被擊倒，不能再發其他動作了
    if (_currentState == ACTION_STATE_KNOCKOUT) {
        goto change_state_failed;
    }
    
    //如果精靈狀態與參數狀態一樣，就沒有必要改變狀態了
    if (_currentState == state) {
        goto change_state_failed;
    }
    
    //改變狀態以前先同志現有動作
    this->stopAllActions();
    
    _currentState = state;
    
    ret = true;
    
    change_state_failed:
    
    return ret;
    
}

Animation *ActionSprite::createAnimation(const char *fmt, int count, float fps)
{
    Vector<SpriteFrame*> frames;

    for (int i = 0; i < count; i++) {//这是一个test
        const char *png = String::createWithFormat(fmt, i)->getCString();
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
        frames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(frames, 1 / fps);
}









