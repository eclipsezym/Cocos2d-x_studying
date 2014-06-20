//
//  GameScene.h
//  FlappyBird
//
//  Created by 韩 剑伟 on 14-2-8.
//
//

#ifndef __FlappyBird__GameScene__
#define __FlappyBird__GameScene__

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public CCLayer {
public:
    bool init();
    CREATE_FUNC(GameScene);
    
    static CCScene* scene();
    
    CCSize screenSize;
    
    void removeNodeSelf(CCNode* node);
    
    void pipeCreate(float dt);
    
    bool isShowingHint;
    void showHint();
    
    void createBird();

    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

    void birdFlyLogic();
    CCArray* pipeArray;
    CCArray* hitCheckArray;

    void restart(CCObject* obj);

    void pipeDownRemove(CCNode* node);
    void pipeUpRemove(CCNode* node);

    int gameScore;
    void update(float dt);

    bool isGameOver;
    void gameOver();
    void showGameOver();
    
    int birdID;
    
    void touchPauseCallBack(CCObject* obj);
    void pauseResume(CCObject* obj);

    void removeGlass(CCNode* node);
};

#endif /* defined(__FlappyBird__GameScene__) */
