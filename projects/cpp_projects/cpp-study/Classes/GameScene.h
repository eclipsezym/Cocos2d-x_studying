//
//  GameScene.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-15.
//
//

#ifndef __cpp_study__GameScene__
#define __cpp_study__GameScene__

#include "cocos2d.h"
#include "GameLayer.h"
#include "OptionLayer.h"


class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);

};



#endif /* defined(__cpp_study__GameScene__) */
