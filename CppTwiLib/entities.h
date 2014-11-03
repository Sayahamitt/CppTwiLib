//
//  entities.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/22.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__entities__
#define __CppTwiLib__entities__

#include <iostream>
#include <vector>

#include "objects.h"

class entities:public Objects{
protected:
    template <typename TYPE>
    bool creatEntitiyArray(std::string objectname,
                           std::string entityname,
                           std::vector<TYPE>& destination){
        if (response.count(objectname) == 0) {
            return false;
        }
        if (response[objectname].is<picojson::array>() == false) {
            return false;
        }
        picojson::array& hashtags = response[objectname].get<picojson::array>();
        
        for (picojson::array::iterator i = hashtags.begin(); i != hashtags.end(); i++) {
            if ((*i).is<picojson::object>() == false) {
                return false;
            }
            picojson::object& hashtag = (*i).get<picojson::object>();
            if (hashtag.count(entityname) == 0) {
                return false;
            }
            destination.push_back(hashtag[entityname].get<std::string>());
        }
        return true;
    }
    
public:
    entities(picojson::object response);
    entities();
    ~entities();
    
    bool getHashTags(std::vector<std::string>& destination);
    bool getUrls(std::vector<std::string>& destination);
    bool getDisplayUrls(std::vector<std::string>& destination);
    bool getUserMentions(std::vector<std::string>& destination);
    
    bool getMediaPageUrls(std::vector<std::string>& destination);
    bool getMediaUrls(std::vector<std::string>& destination);
    bool getMediaUrlsHttps(std::vector<std::string>& destination);
    
    //for user class
    bool getDescriptionUrls(std::vector<std::string>& destination);
};

#endif /* defined(__CppTwiLib__entities__) */
