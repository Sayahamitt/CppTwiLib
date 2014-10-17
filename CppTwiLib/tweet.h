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
class user;

class tweet : public Objects{
protected:
    
public:
    tweet(picojson::object response);
    tweet();
    ~tweet();
    
    bool getCreatedat(std::string& destination);
    bool getID(int64_t& destination);
    bool getinReplytoScreenName(std::string& destination);
    bool getinReplytoStatusID(int64_t& destination);
    bool getRetweetCount(int& destination);
    bool isRetweeted(bool& destination);
    bool getRetweetedStatus(tweet& destination);
    bool getSource(std::string& destination);
    bool getText(std::string& destination);
    bool getUser(user& destination);
    
};

#endif /* defined(__CppTwiLib__tweet__) */
