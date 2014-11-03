//
//  user.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/22.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "user.h"
#include "tweet.h"

user::user(picojson::object response):Objects(response){
}
user::user():Objects(){}
user::~user(){}

bool user::isContibutorEnabled(bool& destination){
    return getValuefromResponse<bool>("contributors_enabled", destination);
}

bool user::getCreatedAt(std::string& destination){
    return getValuefromResponse<std::string>("created_at", destination);
}

bool user::getDescription(std::string& destination){
    return getValuefromResponse<std::string>("description", destination);
}

bool user::getFavouritesCount(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("favourites_count",temp);
    destination = (int)temp;
    
    return res;
}

bool user::isFollowRequestSent(bool &destination){
    return getValuefromResponse<bool>("follow_request_sent", destination);
}

bool user::isFollowing(bool &destination){
    return getValuefromResponse<bool>("following", destination);
}

bool user::getFollowersCount(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("followers_count",temp);
    destination = (int)temp;
    
    return res;}

bool user::getFriendsCount(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("friends_count",temp);
    destination = (int)temp;
    
    return res;}

bool user::getID(int64_t &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("id",temp);
    destination = (int64_t)temp;
    
    return res;
}

bool user::getIDstr(std::string &destination){
    return getValuefromResponse<std::string>("id_str", destination);
}

bool user::getListedCount(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("listed_count",temp);
    destination = (int)temp;
    
    return res;}

bool user::getLocation(std::string &destination){
    return getValuefromResponse<std::string>("location", destination);
}

bool user::getName(std::string &destination){
    return getValuefromResponse<std::string>("name", destination);
}

bool user::isProtected(bool &destination){
    return getValuefromResponse<bool>("protected", destination);
}

bool user::getScreenName(std::string& destination){
    return getValuefromResponse<std::string>("screen_name", destination);
}

bool user::getStatus(tweet &destination){
    picojson::object temp;
    bool res;
    
    res = getValuefromResponse<picojson::object>("status", temp);
    tweet status(temp);
    destination = status;
    
    return res;
}

bool user::getStatusCount(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("statuses_count",temp);
    destination = (int)temp;
    
    return res;
}

bool user::getTimeZone(std::string &destination){
    return getValuefromResponse<std::string>("time_zone", destination);
}

bool user::getURL(std::string &destination){
    return getValuefromResponse<std::string>("url", destination);
}

bool user::getUTCoffset(int &destination){
    bool res;
    double temp;
    
    res = getValuefromResponse<double>("utc_offset",temp);
    destination = (int)temp;
    
    return res;
}

bool user::isVerified(bool &destination){
    return getValuefromResponse<bool>("verified", destination);
}

bool user::getWithheldinCountries(std::string &destination){
    return getValuefromResponse<std::string>("withheld_in_countries", destination);
}

bool user::getWithheldScope(std::string &destination){
    return getValuefromResponse<std::string>("withheld_scope", destination);
}

bool user::getUrls(std::vector<std::string>& destination){
    if (response.count("entities")==0) {
        return false;
    }
    entities entity(response["entities"].get<picojson::object>());
    entity.getUrls(destination);
    
    return true;
}

bool user::getDescriptionUrls(std::vector<std::string>& destination){
    if (response.count("entities")==0) {
        return false;
    }
    entities entity(response["entities"].get<picojson::object>());
    entity.getDescriptionUrls(destination);
    
    return true;
}