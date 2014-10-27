//
//  user.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__user__
#define __CppTwiLib__user__

#include <iostream>
#include <vector>


#include "entities.h"
#include "objects.h"

class tweet;

class user : public Objects{
    
public:
    user(picojson::object response);
    user();
    ~user();
    bool isContibutorEnabled(bool& destination);
    bool getCreatedAt(std::string& destination);
    bool getDescription(std::string& destination);
    //entities getEntities();
    bool getFavouritesCount(int& destination);
    bool isFollowRequestSent(bool& destination);
    bool isFollowing(bool& destination);
    bool getFollowersCount(int& destination);
    bool getFriendsCount(int& destination);
    bool getID(int64_t& destination);
    bool getIDstr(std::string& destination);
    bool getListedCount(int& destination);
    bool getLocation(std::string& destination);
    bool getName(std::string& destination);
    bool isProtected(bool& destination);
    bool getScreenName(std::string& destination);
    bool getStatus(tweet& destination);
    bool getStatusCount(int& destination);
    bool getTimeZone(std::string& destination);
    bool getURL(std::string& destination);
    bool getUTCoffset(int& destination);
    bool isVerified(bool& destination);
    bool getWithheldinCountries(std::string& destination);
    bool getWithheldScope(std::string& destination);
};

#endif /* defined(__CppTwiLib__user__) */
