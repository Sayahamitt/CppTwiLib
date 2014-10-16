//
//  tweet.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__tweet__
#define __CppTwiLib__tweet__

#include <string>

#include "objects.h"
#include "user.h"

class tweet : public Objects{
protected:
    
public:
    tweet(picojson::object response);
    tweet();
    ~tweet();
    
    bool getUser(user& destination);
    
};

#endif /* defined(__CppTwiLib__tweet__) */
