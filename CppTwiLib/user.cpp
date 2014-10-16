//
//  user.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "user.h"

user::user(picojson::object response):Objects(response){
}
user::user():Objects(){}
user::~user(){}

bool user::isContibutor(){
    return response["contributors_enabled"].get<bool>();
}

bool user::getCreatedAt(std::string& destination){
    return getValuefromResponse<std::string>("created_at", destination);
}

bool user::getDescription(std::string& destination){
    return getValuefromResponse<std::string>("description", destination);
}
bool user::getScreenName(std::string& destination){
    return getValuefromResponse<std::string>("screen_name", destination);
}