//
//  ListsResource.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/19.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__ListsResource__
#define __CppTwiLib__ListsResource__

#include "TwitterAPIUser.h"
#include "tweet.h"
#include "user.h"
#include "list.h"

class ListsResource : public TwitterAPIUser{
public:
    ListsResource(std::string c_key, std::string c_sec);
    ListsResource(std::string c_key, std::string c_sec, std::string token, std::string token_sec);
    ListsResource(Twiauth certifyer);
    
    std::vector<list> lists(std::map<std::string, std::string> paramaters);
    std::vector<list> lists(std::string userID);
    std::vector<tweet> statuses(std::string listID,std::map<std::string, std::string> paramaters);
    void members_destroy(std::string listID, std::string userID);
    std::vector<list> memberships(std::map<std::string, std::string> paramaters);
    std::vector<user> subscribers(std::map<std::string, std::string> paramaters);
    void subscribers_destroy(std::string listID);
    list subscribers_create(std::string listID);
    user subscribers_show(std::string listID, std::string userID);
    void members_create_all(std::string listID, std::vector<std::string> userIDarray);
    bool members_show(std::string listID, std::string userID);
    std::vector<user> members(std::string listID);
    void members_create(std::string listID, std::string userID);
    list destory(std::string listID);
    void update(std::map<std::string, std::string> paramaters);
    list create(std::string name, std::map<std::string, std::string> paramaters);
    list show(std::string listID);
    std::vector<list> subscriptions(std::string userID);
    void members_destroy_all(std::string listID,std::vector<std::string> userIDarray);
    std::vector<list> ownerships(std::string userID);
};

#endif /* defined(__CppTwiLib__ListResource__) */
