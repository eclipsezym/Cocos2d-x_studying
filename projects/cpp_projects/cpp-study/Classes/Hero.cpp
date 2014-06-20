//
//  Hero.cpp
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-18.
//
//

#include "Hero.h"
using namespace cocos2d;

Hero::Hero(){}
Hero::~Hero(){}

bool Hero::init()
{
    bool ret = false;
    
    do{
        CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"));
        CallFunc *callbackIdle = CallFunc::create(std::bind(&Hero::idle, this));
        
        Animation *idle = createAnimation("hero_idle_%02d.png", 6, 12);
        setIdleAction(RepeatForever::create(Animate::create(idle)));
        
        Animation *walk = createAnimation("hero_walk_%02d.png", 7, 14);
        setWalkAction(RepeatForever::create(Animate::create(walk)));
        
        Animation *attack = createAnimation("hero_attack_00_%02d.png", 3, 20);
        setAttackAction(Sequence::create(Animate::create(attack),callbackIdle, NULL));
        
        Animation *hurt = createAnimation("hero_hurt_%02d.png", 3, 12);
        setHurtAction(Sequence::create(Animate::create(hurt), callbackIdle, NULL));
        
        Animation *knockout = createAnimation("hero_knockout_%02d.png", 5, 12);
        setKnockoutAction(Sequence::create(Animate::create(knockout), NULL));
        
        setATK(20);
        setHP(100);
        setVelocity(1);
        setDirection(Point::ZERO);
        ret = true;
    }while(0);
    
    return ret;
}
