//
//  list.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/19.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__list__
#define __CppTwiLib__list__

#include <string>

#include "objects.h"
class user;

class list : public Objects{
protected:
    
public:
    list(picojson::object response);
    list();
    ~list();
    
    bool getCreatedat(std::string& destination);
    bool getID(int64_t& destination);
    bool getIDstr(std::string& destination);
    bool getSubscriberCount(int& destination);
    bool getMemberCount(int& destination);
    bool isPublic(bool& destination);
    bool getName(std::string& destination);
    bool getSlug(std::string& destination);
    bool getFullName(std::string& destination);
    bool getDescription(std::string& destination);
    bool getOwnerUser(user& destination);
    bool isFollowing(bool& destination);
};

#endif /* defined(__CppTwiLib__list__) */
