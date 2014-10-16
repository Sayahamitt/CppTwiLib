//
//  tweet.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "tweet.h"

tweet::tweet(picojson::object response):Objects(response){
}

tweet::tweet():Objects(){};

tweet::~tweet(){}

bool tweet::getUser(user& destination){
    picojson::object temp;
    bool res;
    //user account(response["user"].get<picojson::object>());
    
    res = getValuefromResponse<picojson::object>("user", temp);
    
    user account(temp);
    destination = account;
    return res;
}