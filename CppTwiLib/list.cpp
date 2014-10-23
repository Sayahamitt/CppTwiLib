//
//  list.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/19.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "list.h"
#include "user.h"

list::list(picojson::object response):Objects(response){
}

list::list():Objects(){};

list::~list(){}

bool list::getCreatedat(std::string& destination){
    return getValuefromResponse<std::string>("created_at",destination);
}

bool list::getID(int64_t& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("id",temp);
    destination = (int64_t)temp;
    
    return res;
}

bool list::getIDstr(std::string &destination){
    return getValuefromResponse<std::string>("id_str", destination);
}

bool list::getSubscriberCount(int& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("subscriber_count",temp);
    destination = (int)temp;
    
    return res;
}

bool list::getMemberCount(int& destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("member_count",temp);
    destination = (int)temp;
    
    return res;
}

bool list::isPublic(bool& destination){
    bool res;
    std::string temp;
    
    res = getValuefromResponse<std::string>("mode",temp);
    
    if (temp == "public") {
        destination = true;
    }else{
        destination = false;
    }
    return res;
}

bool list::getName(std::string &destination){
    return getValuefromResponse<std::string>("name", destination);
}

bool list::getSlug(std::string &destination){
    return getValuefromResponse<std::string>("slug", destination);
}

bool list::getFullName(std::string &destination){
    return getValuefromResponse<std::string>("full_name", destination);
}

bool list::getDescription(std::string &destination){
    return getValuefromResponse<std::string>("description", destination);
}

bool list::isFollowing(bool& destination){
    return getValuefromResponse<bool>("description", destination);
}

bool list::getOwnerUser(user& destination){
    picojson::object temp;
    bool res;
    
    res = getValuefromResponse<picojson::object>("user", temp);
    
    user account(temp);
    destination = account;
    return res;
}