//
//  StatusResource.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/09.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__StatusResource__
#define __CppTwiLib__StatusResource__

#include "Twistream.h"
#include "tweet.h"

class StatusResource : public Twistream{
public:
    StatusResource(std::string c_key, std::string c_sec);
    StatusResource(std::string c_key, std::string c_sec, std::string token, std::string token_sec);
    StatusResource(Twiauth certifyer);
    
    std::vector<tweet> hometimeline(std::map<std::string, std::string> paramaters);
    std::vector<tweet> user_timeline(std::string screenname, std::map<std::string, std::string> paramaters);
    tweet update(std::string tweet);
};

#endif /* defined(__CppTwiLib__StatusResource__) */
