/*
 * M3AudioManager.cpp
 *
 *  Created on: 2013-1-24
 *      Author: alex
 */

#include "M3AudioManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static M3AudioManager* instance = NULL;

M3AudioManager* M3AudioManager::shareInstance(){
	if(!instance){
		instance = new M3AudioManager();
		instance->init();
	}
	return instance;
}

bool M3AudioManager::init(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sfx_wing.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sfx_hit.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sfx_point.aif");
	return true;
}


void M3AudioManager::playSound(int num){
	std::string path;
	switch(num){
        case SOUND_FLY:
            path = "sfx_wing.caf";
            break;
        case SOUND_HIT:
            path = "sfx_hit.caf";
            break;
        case SOUND_MUSIC:
            path = "sfx_point.aif";
            break;
	}
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(path.c_str());
}

M3AudioManager::~M3AudioManager(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
}

