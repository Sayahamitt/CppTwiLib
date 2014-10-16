//
//  Users.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/09.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "UsersResource.h"

UsersResource::UsersResource(std::string c_key, std::string c_sec):Twistream(c_key, c_sec){
    APIRESOURCENAME = "users";
}

UsersResource::UsersResource(std::string c_key,std::string c_sec, std::string token, std::string token_sec):Twistream(c_key,c_sec,token, token_sec){
    APIRESOURCENAME = "users";
}

user UsersResource::users_lookup(std::map<std::string, std::string> parameters){
    std::string http_header;
    
    http_header = requesttoTwitter(GET,"lookup.json", parameters);
    picojson::object strip;
    user account;
    if (response.is<picojson::array>()){
        picojson::array& timeline = response.get<picojson::array>();
        for (picojson::array::iterator i = timeline.begin(); i != timeline.end(); i++) {
            //std::cout<<"\njson is array"<<std::endl;
            strip = (*i).get<picojson::object>();
        }
        account = user(strip);
    }else{
        strip = response.get<picojson::object>();
        account = user(strip);
    }
    //std::cout<<strResponse<<std::endl;
    //std::string createdat;
    
    return account;
}