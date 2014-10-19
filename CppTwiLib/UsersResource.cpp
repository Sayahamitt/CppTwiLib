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

UsersResource::UsersResource(Twiauth certifyer):Twistream(certifyer){
    APIRESOURCENAME = "users";
}

std::vector<user> UsersResource::lookup(std::vector<std::string>& namelist){
    std::map<std::string, std::string> parameters;
    std::string unitedlist;
    std::vector<user> userlist;
    
    for (std::vector<std::string>::iterator i=namelist.begin(); i != namelist.end(); i++) {
        unitedlist += (*i)+",";
    }unitedlist.erase(unitedlist.end()-1);
    
    parameters["screen_name"]=unitedlist;
    
    requesttoTwitter(GET,"lookup.json", parameters);
    
    createObjectsArray(userlist);
    
    return userlist;
}

user UsersResource::show_id(int64_t ID,std::map<std::string, std::string> parameters){
    user account;
    
    parameters["id"]=std::to_string(ID);
    
    requesttoTwitter(GET, "show.json",parameters);
    
    if (response.is<picojson::object>()){
        account = user(response.get<picojson::object>());
    }
    return account;
}

std::vector<user> UsersResource::search(std::map<std::string, std::string> parameters){
    std::vector<user> userlist;
    
    requesttoTwitter(GET,"search.json", parameters);
    createObjectsArray(userlist);

    return userlist;
}

std::vector<user> UsersResource::contributees(std::string screenname,std::map<std::string, std::string> parameters){
    std::vector<user> userlist;
    
    parameters["screen_name"]=screenname;
    
    requesttoTwitter(GET,"contributees.json", parameters);
    createObjectsArray(userlist);
    
    return userlist;
}

std::vector<user> UsersResource::contributors(std::string screenname,std::map<std::string, std::string> parameters){
    std::vector<user> userlist;
    
    parameters["screen_name"]=screenname;
    
    requesttoTwitter(GET,"contributors.json", parameters);
    createObjectsArray(userlist);
    
    return userlist;
}