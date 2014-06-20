/*
 * M3aAudioManager.h
 *
 *  Created on: 2013-1-24
 *      Author: alex
 */

#ifndef M3AAUDIOMANAGER_H_
#define M3AAUDIOMANAGER_H_

#include "cocos2d.h"

//音效
const static int SOUND_FLY = 0;
const static int SOUND_HIT = 1;
const static int SOUND_MUSIC = 2;


class M3AudioManager : public cocos2d::CCObject{
public:

	~M3AudioManager();
	bool init();
	static M3AudioManager* shareInstance();
    
	void playSound(int num);
};


#endif /* M3AAUDIOMANAGER_H_ */
