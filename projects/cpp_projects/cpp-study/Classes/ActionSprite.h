//
//  ActionSprite.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#ifndef __cpp_study__ActionSprite__
#define __cpp_study__ActionSprite__

#include <cocos2d.h>

typedef enum
{
    ACTION_STATE_NONE = 0,
    ACTION_STATE_IDLE,
    ACTION_STATE_WALK,
    ACTION_STATE_ATTACK,
    ACTION_STATE_HURT,
    ACTION_STATE_KNOCKOUT,

} ActionState;

class ActionSprite : public cocos2d::Sprite
{
public:
    
    ActionSprite();
    ~ActionSprite();
    
    void idle();
    void walk();
    void attack();
    void hurt();
    void knockout();
    
    //定義每個狀態動作的get／set方法
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _hurtAction, HurtAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _knockoutAction, KnockoutAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);

    
    // 精灵的当前状态
    CC_SYNTHESIZE(ActionState, _currentState, ActionState);
   
     CC_SYNTHESIZE(float, _velocity, Velocity); // 移动速度
//    CC_SYNTHESIZE(cocos2d::Point, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::Point, _direction, Direction); // 移动方向（向量）
    CC_SYNTHESIZE(unsigned int, _hp, HP); // 生命值
    CC_SYNTHESIZE(unsigned int, _atk, ATK); // 攻击力

protected:
    // 定义一个创建状态动画的方法
    // fmt   - 状态的图片名格式(查看pd_sprites.plist,每种状态格式都类似hero_idle_xx.png)
    // count - 状态图片序列的数量
    // fps   - 动画的播放帧率
    
    static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);
  
private:
    bool _changeState(ActionState state);
};

#endif /* defined(__cpp_study__ActionSprite__) */
