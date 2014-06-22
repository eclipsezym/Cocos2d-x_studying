//
//  GameLayer.cpp
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#include "GameLayer.h"
#include <Hero.h>
#include <Robot.h>
using namespace cocos2d;


GameLayer::GameLayer(){}

GameLayer::~GameLayer(){}


bool GameLayer::init()
{

    bool ret = false;
    
    do{
    
        CC_BREAK_IF(!Layer::init());
        
        _map = TMXTiledMap::create("pd_tilemap.tmx");
        
        this->addChild(_map);
        
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
        _actors = SpriteBatchNode::create("pd_sprites.pvr.ccz");
        this->addChild(_actors);
        
        _hero = Hero::create();
        _hero->setPosition(Point(80, 80));
        _hero->idle();
        
        _actors->addChild(_hero);
        
        
        for (int i = 0; i < 5; i++) {
            Robot *robot = Robot::create();
            robot->setPosition(Point(CCRANDOM_0_1() * 400, CCRANDOM_0_1() * 100));
            robot->idle();
            _robots.pushBack(robot);
            _actors->addChild(robot);
        }

        ret = true;
        
    }while (0);
        
    return ret;
}

void GameLayer::onAttack()
{
    _hero->attack();
    
//    auto robot = _robots.begin();
//    while (robot != _robots.end()) {
//        if (_hero->boundingBox()) {
//            <#statements#>
//        }
//
//        robot++;
//    }

    
}

void GameLayer::onWalk(cocos2d::Point direction, float distance)
{
    _hero->setFlippedX(direction.x < 0 ? true : false);
    _hero->walk();
    _heroVelocity = direction * (distance < 96 ? 2 : 4);
}

void GameLayer::onStop()
{
    _hero->idle();
}


void GameLayer::update(float dt)
{
    if (_hero->getActionState() == ACTION_STATE_WALK) {
        _hero->setPosition(_hero->getPosition() + _heroVelocity);
    }
}

void GameLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{

    update(0);
}



