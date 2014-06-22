//
//  GameLayer.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#ifndef __cpp_study__GameLayer__
#define __cpp_study__GameLayer__

#include <cocos2d.h>
#include <ActionSprite.h>
#include <Robot.h>
#include "OptionDelegate.h"

class GameLayer : public cocos2d::Layer, public OptionDelegate
{
public:
    GameLayer();
    ~GameLayer();
    
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
    void onWalk(cocos2d::Point direction, float distance);
    
    void onAttack();
    
    void onStop();
    
    
    void update(float dt);
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated);
    
private:
    cocos2d::TMXTiledMap *_map;
    
    ActionSprite *_hero;
    
    cocos2d::Vector<Robot*> _robots;

    cocos2d::SpriteBatchNode *_actors;
    
    cocos2d::Point _heroVelocity;

};


#endif /* defined(__cpp_study__GameLayer__) */
