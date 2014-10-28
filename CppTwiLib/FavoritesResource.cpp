//
//  FavoritesResource.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/19.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "FavoritesResource.h"

FavoritesResource::FavoritesResource(std::string c_key, std::string c_sec):TwitterAPIUser(c_key, c_sec){
    APIRESOURCENAME = "favorites";
}

FavoritesResource::FavoritesResource(std::string c_key,std::string c_sec, std::string token, std::string token_sec):TwitterAPIUser(c_key,c_sec,token, token_sec){
    APIRESOURCENAME = "favorites";
}

FavoritesResource::FavoritesResource(Twiauth certifyer):TwitterAPIUser(certifyer){
    APIRESOURCENAME = "favorites";
}

std::vector<tweet> FavoritesResource::list(std::map<std::string, std::string> paramaters){
    std::vector<tweet> favlist;
    
    requesttoTwitter(GET,"list.json", paramaters);
    
    createObjectsArray(favlist);
    return favlist;
}

tweet FavoritesResource::destroy(int64_t statusID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=std::to_string(statusID);
    
    requesttoTwitter(POST, "destroy/.json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

tweet FavoritesResource::create(int64_t statusID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=std::to_string(statusID);
    
    requesttoTwitter(POST, "create/.json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}