//
//  GameScene.cpp
//  FlappyBird
//
//  Created by 韩 剑伟 on 14-2-8.
//
//

#include "GameScene.h"
#include "CCShake.h"
#include "NoTouchLayer.h"
#include "M3AudioManager.h"

static float randomValue;

static const int TAG_HINT = 666;

static const int TAG_BIRD = 667;

static const int TAG_LAND = 668;

static const int TAG_MASK = 669;
static const int TAG_TITLE = 670;
static const int TAG_NO_LAYER = 671;
static const int TAG_RESUME = 672;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    screenSize = CCDirector::sharedDirector()->getWinSize();
    
    int r = CCRANDOM_0_1() * 10;
    
    CCSprite* bg = NULL;
    if (r >= 5) {
        bg = CCSprite::createWithSpriteFrameName("bg_day.png");
    } else {
        bg = CCSprite::createWithSpriteFrameName("bg_night.png");
    }
    bg->setAnchorPoint(ccp(0, 0));
    bg->setPosition(ccp(0, 0));
    addChild(bg, 0);
    
    CCSprite* land0 = CCSprite::createWithSpriteFrameName("land.png");
    land0->setAnchorPoint(ccp(0, 0));
    land0->setPosition(ccp(0, 0));
    addChild(land0, 3, TAG_LAND);
    CCMoveBy* move = CCMoveBy::create(1.0f, ccp(-land0->getContentSize().width * 0.25f, 0));
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(GameScene::removeNodeSelf));
    CCSequence* seq = CCSequence::create(move, call, NULL);
    land0->runAction(seq);
    
    randomValue = 0;
    gameScore = 0;
    isGameOver = false;
    isShowingHint = true;
    
    pipeArray = CCArray::create();
    CC_SAFE_RETAIN(pipeArray);
    hitCheckArray = CCArray::create();
    CC_SAFE_RETAIN(hitCheckArray);
    
    createBird();
    showHint();
    
    CCMenuItemSprite* pauseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button_pause.png"), NULL, this, menu_selector(GameScene::touchPauseCallBack));
    pauseItem->setPosition(ccp(screenSize.width * 0.92f, screenSize.height * 0.95f));
    pauseItem->setScale(2.0f);
    CCMenu* m = CCMenu::create(pauseItem, NULL);
    m->setPosition(CCPointZero);
    addChild(m, 10);
    
    M3AudioManager::shareInstance();
    return true;
}

void GameScene::touchPauseCallBack(CCObject* obj) {
    if (isGameOver) {
        return;
    }
    
    CCDirector::sharedDirector()->pause();
    
    NoTouchLayer* n = NoTouchLayer::create();
    addChild(n, 10, TAG_NO_LAYER);
    
    CCSprite* mask = CCSprite::createWithSpriteFrameName("mask.png");
    mask->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    mask->setScaleX(screenSize.width / mask->getContentSize().width * 1.5f);
    mask->setScaleY(screenSize.height / mask->getContentSize().height * 1.5f);
    addChild(mask, 10, TAG_MASK);
    
    CCSprite* pause = CCSprite::createWithSpriteFrameName("pause.png");
    pause->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.68f));
    pause->setScale(1.5f);
    addChild(pause, 10, TAG_TITLE);
    
    CCMenuItemSprite* item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("resume.png"), NULL, this, menu_selector(GameScene::pauseResume));
    item->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.3f));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    menu->setTouchPriority(-200000);
    addChild(menu, 10, TAG_RESUME);
}

void GameScene::pauseResume(CCObject* obj) {
    CCDirector::sharedDirector()->resume();
    
    removeChildByTag(TAG_NO_LAYER, true);
    removeChildByTag(TAG_MASK, true);
    removeChildByTag(TAG_TITLE, true);
    removeChildByTag(TAG_RESUME, true);
}

void GameScene::removeNodeSelf(CCNode* node)
{
    node->removeFromParentAndCleanup(true);
    
    CCSprite* land0 = CCSprite::createWithSpriteFrameName("land.png");
    land0->setAnchorPoint(ccp(0, 0));
    land0->setPosition(ccp(0, 0));
    addChild(land0, 3, TAG_LAND);
    
    CCMoveBy* move = CCMoveBy::create(1.0f, ccp(-land0->getContentSize().width * 0.25f, 0));
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(GameScene::removeNodeSelf));
    CCSequence* seq = CCSequence::create(move, call, NULL);
    land0->runAction(seq);
}

void GameScene::pipeCreate(float dt)
{
    randomValue = 18 + CCRANDOM_0_1() * 50;
    
    CCSprite* pipeUp = CCSprite::createWithSpriteFrameName("pipe_up.png");
    pipeUp->setAnchorPoint(ccp(0.5f, 0));
    pipeUp->setPosition(ccp(screenSize.width * 1.2f, -randomValue * pipeUp->getContentSize().height / 100));
    addChild(pipeUp, 2);
    
    CCSprite* pipeDown = CCSprite::createWithSpriteFrameName("pipe_down.png");
    pipeDown->setAnchorPoint(ccp(0.5f, 0));
    pipeDown->setPosition(ccp(pipeUp->getPositionX(), pipeUp->getPositionY() + pipeUp->getContentSize().height + screenSize.height * 0.19f));
    addChild(pipeDown, 2);
    CCMoveBy* move = CCMoveBy::create(4.0f, ccp(-1000, 0));
    CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(GameScene::pipeUpRemove));
    CCSequence* seq = CCSequence::create(move, call, NULL);
    pipeUp->runAction(seq);
    
    pipeUp->setUserData((void*)0);
    pipeArray->addObject(pipeUp);
    
    CCCallFuncN* downCall = CCCallFuncN::create(this, callfuncN_selector(GameScene::pipeDownRemove));
    CCSequence* downSeq = CCSequence::create((CCActionInterval*)(move->copy()->autorelease()), downCall, NULL);
    pipeDown->runAction(downSeq);
    
    hitCheckArray->addObject(pipeUp);
    hitCheckArray->addObject(pipeDown);
}

void GameScene::pipeDownRemove(CCNode* node) {
    node->removeFromParentAndCleanup(true);
    hitCheckArray->removeObject(node);
}

void GameScene::pipeUpRemove(CCNode* node) {
    pipeArray->removeObject(node);
    hitCheckArray->removeObject(node);
    node->removeFromParentAndCleanup(true);
}

void GameScene::update(float dt) {
    CCSprite* bird = (CCSprite*)getChildByTag(TAG_BIRD);
    
    if (bird->getPositionY() >= screenSize.height) {
        bird->setPositionY(screenSize.height);
    }
    
    CCRect birdRect = CCRectMake(bird->getPositionX() - bird->getContentSize().width * 0.45f, bird->getPositionY() - bird->getContentSize().height * 0.45f,
                                 bird->getContentSize().width * 0.9f, bird->getContentSize().height * 0.9f);
    
    
    if (isGameOver) {
        CCSprite* land = (CCSprite*)getChildByTag(TAG_LAND);
        CCRect landRect = CCRectMake(land->getPositionX(), land->getPositionY(),
                                     land->getContentSize().width * 0.9f, land->getContentSize().height * 0.97f);
        if (landRect.intersectsRect(birdRect)) {
            bird->stopAllActions();
            unscheduleUpdate();
            showGameOver();
        }
        return;
    }
    
    CCSprite* land = (CCSprite*)getChildByTag(TAG_LAND);
    CCRect landRect = CCRectMake(land->getPositionX(), land->getPositionY(),
                                 land->getContentSize().width * 0.9f, land->getContentSize().height * 0.97f);
    if (landRect.intersectsRect(birdRect)) {
        isGameOver = true;
        bird->stopAllActions();
        unscheduleAllSelectors();
        
        CCShake* shake = CCShake::create(0.6f, 15);
        runAction(shake);
        M3AudioManager::shareInstance()->playSound(SOUND_HIT);
        
        for (int i = 0; i < hitCheckArray->count(); i++) {
            CCSprite* pipe = (CCSprite*)hitCheckArray->objectAtIndex(i);
            pipe->stopAllActions();
        }
        CCSprite* land = (CCSprite*)getChildByTag(TAG_LAND);
        land->stopAllActions();
        
        showGameOver();
        return;
    }
    

    
    for (int i = 0; i < hitCheckArray->count(); i++) {
        CCSprite* pipe = (CCSprite*)(hitCheckArray->objectAtIndex(i));
        CCRect pipeRect = CCRectMake(pipe->getPositionX() - pipe->getContentSize().width * 0.45f, pipe->getPositionY() + screenSize.height * 0.03f,
                                     pipe->getContentSize().width * 0.9f, pipe->getContentSize().height * 0.925f);
        if (pipeRect.intersectsRect(birdRect)) {
            CCShake* shake = CCShake::create(0.6f, 15);
            runAction(shake);
            M3AudioManager::shareInstance()->playSound(SOUND_HIT);
            gameOver();
            return;
        }
    }
    
    
    for (int i = 0; i < pipeArray->count(); i++) {
        CCSprite* pipe = (CCSprite*)(pipeArray->objectAtIndex(i));
        int uData = (int)pipe->getUserData();
        if (uData == 0 && pipe->getPositionX() <= screenSize.width * 0.25f) {
            pipe->setUserData((void*)1);
            
            gameScore += 1;
            CCLabelAtlas* score = (CCLabelAtlas*)getChildByTag(999);
            score->setString(CCString::createWithFormat("%d", gameScore)->getCString());
            
            M3AudioManager::shareInstance()->playSound(SOUND_MUSIC);
            
            if (gameScore == 15) {
                CCSprite* glass = CCSprite::createWithSpriteFrameName("glass.png");
                glass->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
                addChild(glass, 100);
                
                CCDelayTime* delay = CCDelayTime::create(2.0f);
                CCCallFuncN* c = CCCallFuncN::create(this, callfuncN_selector(GameScene::removeGlass));
                CCSequence* seq = CCSequence::create(delay, c, NULL);
                glass->runAction(seq);
                
                M3AudioManager::shareInstance()->playSound(SOUND_HIT);
            }
            break;
        }
    }
}

void GameScene::removeGlass(CCNode* node) {
    node->removeFromParentAndCleanup(true);
}

void GameScene::showHint() {
    CCSprite* hint = CCSprite::createWithSpriteFrameName("tutorial.png");
    hint->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.45f));
    addChild(hint, 5, TAG_HINT);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    setTouchEnabled(true);
}

void GameScene::createBird() {
    birdID = CCRANDOM_0_1() * 3;
    
    CCString* bName = CCString::createWithFormat("bird%d_0.png", birdID);
    CCSprite* bird = CCSprite::createWithSpriteFrameName(bName->getCString());
    bird->setPosition(ccp(screenSize.width * 0.25f, screenSize.height * 0.5f));
    addChild(bird, 4, TAG_BIRD);
    
    CCAnimation* animation = CCAnimation::create();
    for (int i = 0; i < 3; i++) {
        CCString* birdName = CCString::createWithFormat("bird%d_%d.png", birdID, i);
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
}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
    if (isGameOver) {
        return true;
    }
    
    if (isShowingHint) {
        removeChildByTag(TAG_HINT, true);
        isShowingHint = false;
        
        CCSprite* bird = (CCSprite*)getChildByTag(TAG_BIRD);
        if (bird) {
            bird->stopAllActions();
            
            CCAnimation* animation = CCAnimation::create();
            for (int i = 0; i < 3; i++) {
                CCString* birdName = CCString::createWithFormat("bird%d_%d.png", birdID, i);
                CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(birdName->getCString());
                animation->addSpriteFrame(frame);
            }
            animation->setDelayPerUnit(0.08f);
            CCAnimate* animate = CCAnimate::create(animation);
            CCRepeatForever* repeat = CCRepeatForever::create(animate);
            bird->runAction(repeat);
        }
        CCLabelAtlas* score = CCLabelAtlas::create("0", "score_number.png", 30, 45, '0');
        score->setAnchorPoint(ccp(0.5f, 0.5f));
        score->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.85f));
        score->setScale(1.5f);
        addChild(score, 10, 999);
        
        schedule(schedule_selector(GameScene::pipeCreate), 1.5f, 99999, 2.0f);
        scheduleUpdate();
    }
    
    birdFlyLogic();
    
    return true;
}

void GameScene::birdFlyLogic() {
    M3AudioManager::shareInstance()->playSound(SOUND_FLY);
    
    CCSprite* bird = (CCSprite*)getChildByTag(TAG_BIRD);
    bird->stopActionByTag(100);
    
    bird->setRotation(340);
    
    CCMoveBy* moveUp = CCMoveBy::create(0.2f, ccp(0, bird->getContentSize().height * 1.25f));
    CCEaseOut* upEout = CCEaseOut::create(moveUp, 2.25f);
    
    CCDelayTime* delay = CCDelayTime::create(0.2f);
    CCRotateBy* rotate = CCRotateBy::create(0.35f, 75);
    CCSequence* seq0 = CCSequence::create(delay, rotate, NULL);
    
    CCMoveBy* moveDown = CCMoveBy::create(1.5f, ccp(0, -screenSize.height * 1.5f));
    CCEaseIn* downIn = CCEaseIn::create(moveDown, 1.95f);
    
    CCSpawn* spawn = CCSpawn::create(seq0, downIn, NULL);
    
    CCSequence* seq = CCSequence::create(upEout, spawn, NULL);
    seq->setTag(100);
    bird->runAction(seq);
}

void GameScene::gameOver() {
    isGameOver = true;
    unscheduleAllSelectors();
    
    scheduleUpdate();
    
    for (int i = 0; i < hitCheckArray->count(); i++) {
        CCSprite* pipe = (CCSprite*)hitCheckArray->objectAtIndex(i);
        pipe->stopAllActions();
    }
    CCSprite* land = (CCSprite*)getChildByTag(TAG_LAND);
    land->stopAllActions();
}

void GameScene::showGameOver() {
    CCSprite* over = CCSprite::createWithSpriteFrameName("gameOver.png");
    over->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.7f));
    over->setScale(1.5f);
    addChild(over, 10);
    
    CCSprite* scoreBoard = CCSprite::createWithSpriteFrameName("score_board.png");
    scoreBoard->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    scoreBoard->setScale(1.5f);
    addChild(scoreBoard, 10);
    
    CCLabelAtlas* curScore = CCLabelAtlas::create(CCString::createWithFormat("%d", gameScore)->getCString(), "score_number.png", 30, 45, '0');
    curScore->setAnchorPoint(ccp(1, 0.5f));
    curScore->setScale(0.75f);
    curScore->setPosition(ccp(screenSize.width * 0.78f, screenSize.height * 0.53f));
    addChild(curScore, 10);
    
    int maxScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("MAX", 0);
    if (gameScore > maxScore) {
        maxScore = gameScore;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("MAX", gameScore);
        CCUserDefault::sharedUserDefault()->flush();
        CCSprite* showNew = CCSprite::createWithSpriteFrameName("new.png");
        showNew->setAnchorPoint(ccp(0, 0.5f));
        showNew->setScale(1.5f);
        showNew->setPosition(ccp(screenSize.width * 0.78f, screenSize.height * 0.45f));
        addChild(showNew, 10);
    }
    
    CCLabelAtlas* highScore = CCLabelAtlas::create(CCString::createWithFormat("%d", maxScore)->getCString(), "score_number.png", 30, 45, '0');
    highScore->setAnchorPoint(ccp(1, 0.5f));
    highScore->setScale(0.75f);
    highScore->setPosition(ccp(screenSize.width * 0.78f, screenSize.height * 0.45f));
    addChild(highScore, 10);
    
    removeChildByTag(999);
    
    CCMenuItemSprite* item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start.png"), CCSprite::createWithSpriteFrameName("start.png"), this, menu_selector(GameScene::restart));
    item->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.3f));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu, 10);
    
    if (gameScore >= 10) {
        CCSprite* metalName = NULL;
        if (gameScore >= 10 && gameScore < 50) {
            metalName = CCSprite::createWithSpriteFrameName("medals_1.png");
        } else if (gameScore >= 50 && gameScore < 100) {
            metalName = CCSprite::createWithSpriteFrameName("medals_2.png");
        } else if (gameScore >= 100) {
            metalName = CCSprite::createWithSpriteFrameName("medals_3.png");
        }
        metalName->setScale(1.5f);
        metalName->setPosition(ccp(screenSize.width * 0.3f, screenSize.height * 0.495f));
        addChild(metalName, 10);
    }
}

void GameScene::restart(CCObject* obj) {
    CC_SAFE_RELEASE(pipeArray);
    CC_SAFE_RELEASE(hitCheckArray);
    
    stopAllActions();
    unscheduleAllSelectors();
    
    CCMenuItemSprite* item = (CCMenuItemSprite*)obj;
    CCScaleTo* scale = CCScaleTo::create(0.1f, 1.2f);
    CCScaleTo* scale2 = CCScaleTo::create(0.1f, 1.0f);
    CCSequence* seq = CCSequence::create(scale, scale2, NULL);
    item->runAction(seq);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, GameScene::scene()));
}


