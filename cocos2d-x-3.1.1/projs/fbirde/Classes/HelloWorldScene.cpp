#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#include "GameScene.h"

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{    
    screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::createWithSpriteFrameName("bg_day.png");
    bg->setAnchorPoint(ccp(0, 0));
    bg->setPosition(ccp(0, 0));
    addChild(bg, 0);

    CCSprite* bird = CCSprite::createWithSpriteFrameName("bird0_0.png");
    bird->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    addChild(bird, 1);
    
    CCAnimation* animation = CCAnimation::create();
    for (int i = 0; i < 3; i++) {
        CCString* birdName = CCString::createWithFormat("bird0_%d.png", i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdName->getCString());
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(0.08f);
    CCAnimate* animate = CCAnimate::create(animation);
    CCRepeat* br = CCRepeat::create(animate, 2);
    
    CCMoveBy* moveUp = CCMoveBy::create(0.5f, ccp(0, -bird->getContentSize().height * 0.4f));
    CCMoveBy* moveDown = CCMoveBy::create(0.5f, ccp(0, bird->getContentSize().height * 0.4f));
    CCSequence* moveSeq = CCSequence::create(moveUp, moveDown, NULL);
    
    CCSpawn* spawn = CCSpawn::create(br, moveSeq, NULL);
    
    CCRepeatForever* repeat = CCRepeatForever::create(spawn);
    bird->runAction(repeat);
    
    CCSprite* logo = CCSprite::createWithSpriteFrameName("logo.png");
    logo->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.65f));
    addChild(logo, 1);
    
    CCSprite* land0 = CCSprite::createWithSpriteFrameName("land.png");
    land0->setAnchorPoint(ccp(0, 0));
    land0->setPosition(ccp(0, 0));
    addChild(land0, 3);
    CCMoveBy* move = CCMoveBy::create(1.5f, ccp(-land0->getContentSize().width * 0.25f, 0));
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::removeNodeSelf));
    CCSequence* seq = CCSequence::create(move, call, NULL);
    land0->runAction(seq);
    
    CCMenuItemSprite* item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start.png"), CCSprite::createWithSpriteFrameName("start.png"), this, menu_selector(HelloWorld::startCallBack));
    item->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.3f));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu, 1);
    return true;
}

void HelloWorld::startCallBack(CCObject* obj)
{
    CCMenuItemSprite* item = (CCMenuItemSprite*)obj;
    CCScaleTo* scale = CCScaleTo::create(0.1f, 1.2f);
    CCScaleTo* scale2 = CCScaleTo::create(0.1f, 1.0f);
    CCSequence* seq = CCSequence::create(scale, scale2, NULL);
    item->runAction(seq);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, GameScene::scene()));
}

void HelloWorld::removeNodeSelf(CCNode* node)
{
    node->removeFromParentAndCleanup(true);

    CCSprite* land0 = CCSprite::createWithSpriteFrameName("land.png");
    land0->setAnchorPoint(ccp(0, 0));
    land0->setPosition(ccp(0, 0));
    addChild(land0, 3);
    
    CCMoveBy* move = CCMoveBy::create(1.5f, ccp(-land0->getContentSize().width * 0.25f, 0));
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::removeNodeSelf));
    CCSequence* seq = CCSequence::create(move, call, NULL);
    land0->runAction(seq);
}


