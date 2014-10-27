//
//  StatusResource.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
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
    
    std::vector<tweet> mentions_timeline(std::map<std::string, std::string> paramaters);
    std::vector<tweet> hometimeline(std::map<std::string, std::string> paramaters);
    std::vector<tweet> user_timeline(std::string screenname, std::map<std::string, std::string> paramaters);
    std::vector<tweet> retweets_of_me(std::map<std::string, std::string> paramaters);
    std::vector<tweet> retweets_id(int64_t ID,std::map<std::string, std::string> paramaters);
    tweet show_id(int64_t ID,std::map<std::string, std::string> paramaters);
    tweet destory_id(int64_t ID);
    tweet update(std::string tweet);
    tweet retweet_id(int64_t ID);
    std::vector<int64_t> retweeters_ids(int64_t ID);

};

#endif /* defined(__CppTwiLib__StatusResource__) */
