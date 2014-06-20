//
//  Robot.h
//  cpp-study
//
//  Created by Yueming Zhang on 14-6-18.
//
//

#ifndef __cpp_study__Robot__
#define __cpp_study__Robot__

#include <ActionSprite.h>

class Robot : public ActionSprite
{
public:
    Robot();
    ~Robot();
    
    bool init();
    CREATE_FUNC(Robot);
};

#endif /* defined(__cpp_study__Robot__) */
