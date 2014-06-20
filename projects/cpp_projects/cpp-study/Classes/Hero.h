//
//  Hero.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-18.
//
//

#ifndef __cpp_study__Hero__
#define __cpp_study__Hero__

#include <ActionSprite.h>

class Hero : public ActionSprite
{
public:
    Hero();
    ~Hero();
    
    bool init();    
    CREATE_FUNC(Hero);
};

#endif /* defined(__cpp_study__Hero__) */
