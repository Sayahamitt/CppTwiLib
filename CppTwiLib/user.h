//
//  user.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__user__
#define __CppTwiLib__user__

#include <iostream>
#include <vector>


#include "entities.h"
#include "objects.h"

class user : public Objects{
    
public:
    user(picojson::object response);
    user();
    ~user();
    bool isContibutor();
    bool getCreatedAt(std::string& destination);
    bool getDescription(std::string& destination);
    //entities getEntities();
    
    bool getScreenName(std::string& destination);
};

#endif /* defined(__CppTwiLib__user__) */
