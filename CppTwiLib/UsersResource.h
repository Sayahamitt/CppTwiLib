//
//  Users.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__Users__
#define __CppTwiLib__Users__
#include "TwitterAPIUser.h"
#include "user.h"

class UsersResource : public TwitterAPIUser{
public:
    UsersResource(std::string c_key, std::string c_sec);
    UsersResource(std::string c_key, std::string c_sec, std::string token, std::string token_sec);
    UsersResource(Twiauth certifyer);
    
    std::vector<user> lookup(std::vector<std::string>& namelist);
    user show_id(std::string userID,std::map<std::string, std::string> parameters);
    std::vector<user> search(std::map<std::string, std::string> parameters);
    /*以下テスト未実施。
    std::vector<user> contributees(std::string screenname,std::map<std::string, std::string> parameters);
    std::vector<user> contributors(std::string screenname,std::map<std::string, std::string> parameters);
     */
};
#endif /* defined(__CppTwiLib__Users__) */
