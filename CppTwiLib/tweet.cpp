//
//  tweet.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "tweet.h"
#include "user.h"

tweet::tweet(picojson::object response):Objects(response){
}

tweet::tweet():Objects(){};

tweet::~tweet(){}

bool tweet::getCreatedat(std::string& destination){
    return getValuefromResponse<std::string>("created_at",destination);
}

bool tweet::getID(int64_t& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("id",temp);
    destination = (int64_t)temp;
    
    return res;
}

bool tweet::getinReplytoScreenName(std::string& destination){
    return getValuefromResponse<std::string>("in_reply_to_screen_name",destination);
}

bool tweet::getinReplytoStatusID(int64_t& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("in_reply_to_screen_name",temp);
    destination = (int64_t)temp;
    
    return res;
}

bool tweet::getRetweetCount(int& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("retweet_count",temp);
    destination = (int)temp;
    
    return res;
}

bool tweet::isRetweeted(bool &destination){
    return getValuefromResponse<bool>("retweeted", destination);
}

bool tweet::getRetweetedStatus(tweet& destination){
    picojson::object temp;
    bool res;
    
    res = getValuefromResponse<picojson::object>("retweeted_status", temp);
    tweet status(temp);
    destination = status;
    
    return res;
}

bool tweet::getSource(std::string &destination){
    return getValuefromResponse<std::string>("source",destination);
}

bool tweet::getText(std::string& destination){
    return getValuefromResponse<std::string>("text",destination);
}

bool tweet::getUser(user& destination){
    picojson::object temp;
    bool res;
    //user account(response["user"].get<picojson::object>());
    
    res = getValuefromResponse<picojson::object>("user", temp);
    
    user account(temp);
    destination = account;
    return res;
}