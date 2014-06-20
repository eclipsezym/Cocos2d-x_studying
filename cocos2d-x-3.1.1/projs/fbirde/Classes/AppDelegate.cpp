//
//  FlappyBirdAppDelegate.cpp
//  FlappyBird
//
//  Created by 韩 剑伟 on 14-2-8.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
//    Director *pDirector = Director::getInstance();
//    pDirector->setOpenGLView(EGLView::getEAGLView()());
//    
//    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionShowAll);
    
    auto pDirector = Director::getInstance();
    auto eglView = pDirector->getOpenGLView();
    eglView->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
    
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("resss.plist");

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
