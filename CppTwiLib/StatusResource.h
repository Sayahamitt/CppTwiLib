//
//  StatusResource.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__StatusResource__
#define __CppTwiLib__StatusResource__

#include "TwitterAPIUser.h"
#include "tweet.h"

class StatusResource : public TwitterAPIUser{
public:
    StatusResource(std::string c_key, std::string c_sec);
    StatusResource(std::string c_key, std::string c_sec, std::string token, std::string token_sec);
    StatusResource(Twiauth certifyer);
    
    std::vector<tweet> mentions_timeline(std::map<std::string, std::string> paramaters);
    std::vector<tweet> hometimeline(std::map<std::string, std::string> paramaters);
    
    std::vector<tweet> user_timeline(std::string screenname, std::map<std::string, std::string> paramaters);
    std::vector<tweet> user_timeline(std::string screenname);
    std::vector<tweet> user_timeline(std::map<std::string,std::string> paramaters);
    
    std::vector<tweet> retweets_of_me(std::map<std::string, std::string> paramaters);
    
    std::vector<tweet> retweets_id(std::string tweetID,std::map<std::string, std::string> paramaters);
    std::vector<tweet> retweets_id(std::string tweetID);
    
    tweet show_id(std::string tweetID,std::map<std::string, std::string> paramaters);
    tweet show_id(std::string tweetID);
    
    tweet destory_id(std::string tweetID);
    tweet update(std::string status);
    tweet retweet_id(std::string tweetID);
    std::vector<int64_t> retweeters_ids(std::string tweetID);

};

#endif /* defined(__CppTwiLib__StatusResource__) */
