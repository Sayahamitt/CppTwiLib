//
//  entities.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/22.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "entities.h"

entities::entities(picojson::object response):Objects(response){
    if (response.count("entities") == 1) {
        if (response["entities"].is<picojson::object>() == true) {
            this->setJson(response["entities"].get<picojson::object>());
        }
    }
}
entities::entities():Objects(){}
entities::~entities(){}

bool entities::getHashTags(std::vector<std::string> &destination){
    
    return creatEntitiyArray("hashtags", "text", destination);
}

bool entities::getUrls(std::vector<std::string>& destination){
    
    return creatEntitiyArray("urls", "url", destination);
}

bool entities::getDisplayUrls(std::vector<std::string>& destination){
    
    return creatEntitiyArray("urls", "display_url", destination);
}

bool entities::getUserMentions(std::vector<std::string>& destination){
    
    return creatEntitiyArray("user_mentions", "screen_name", destination);
}

bool entities::getMediaPageUrls(std::vector<std::string>& destination){
    
    return creatEntitiyArray("media", "url", destination);
}

bool entities::getMediaUrls(std::vector<std::string>& destination){
    
    return creatEntitiyArray("media", "media_url", destination);
}

bool entities::getMediaUrlsHttps(std::vector<std::string>& destination){
    
    return creatEntitiyArray("media", "media_url_https", destination);
}

bool entities::getDescriptionUrls(std::vector<std::string>& destination){
    
    return creatEntitiyArray("description", "urls", destination);
}