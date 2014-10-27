//
//  StatusResource.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/09.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "StatusResource.h"

#include <sstream>

StatusResource::StatusResource(std::string c_key, std::string c_sec):Twistream(c_key, c_sec){
    APIRESOURCENAME = "statuses";
}

StatusResource::StatusResource(std::string c_key,std::string c_sec, std::string token, std::string token_sec):Twistream(c_key,c_sec,token, token_sec){
    APIRESOURCENAME = "statuses";
}

StatusResource::StatusResource(Twiauth certifyer):Twistream(certifyer){
    APIRESOURCENAME = "statuses";
}

std::vector<tweet> StatusResource::mentions_timeline(std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    
    requesttoTwitter(GET,"mentions_timeline.json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}

std::vector<tweet> StatusResource::hometimeline(std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    std::string http_header;
    
    http_header = requesttoTwitter(GET,"home_timeline.json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}


std::vector<tweet> StatusResource::user_timeline(std::string screenname,std::map<std::string, std::string> paramaters){
    std::vector<tweet> timeline;
    std::string http_header;
    
    paramaters["screen_name"]=screenname;
    
    http_header = requesttoTwitter(GET, "user_timeline.json",paramaters);
    
    createObjectsArray(timeline);

    return timeline;
}

std::vector<tweet> StatusResource::retweets_of_me(std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    
    requesttoTwitter(GET,"retweets_of_me.json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}

std::vector<tweet> StatusResource::retweets_id(int64_t ID,std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    
    paramaters.erase("id");
    
    requesttoTwitter(GET,"retweets/"+std::to_string(ID)+".json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}

tweet StatusResource::show_id(int64_t ID,std::map<std::string, std::string> paramaters){
    tweet status;
    
    paramaters["id"]=std::to_string(ID);
    
    requesttoTwitter(GET, "show.json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

tweet StatusResource::destory_id(int64_t ID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=std::to_string(ID);
    
    requesttoTwitter(POST, "destroy/"+std::to_string(ID)+".json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

tweet StatusResource::update(std::string poststr){
    std::map<std::string, std::string> param;
    std::string http_header;
    tweet posted;
    
    poststr = StringtoURLencode(poststr);
    param["status"]=poststr;
    
    http_header = requesttoTwitter(POST, "update.json", param);
    
    if (response.is<picojson::object>()){
        posted = tweet(response.get<picojson::object>());
    }
    
    return posted;
}

tweet StatusResource::retweet_id(int64_t ID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=std::to_string(ID);
    
    requesttoTwitter(POST, "retweet/"+std::to_string(ID)+".json", paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

std::vector<int64_t> StatusResource::retweeters_ids(int64_t ID){
    std::map<std::string, std::string> param;
    std::vector<int64_t> retweeters;
    picojson::array ids;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "retweeters/ids.json",param);
        if (!response.is<picojson::object>()) {
            return retweeters;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        ids = resObj["ids"].get<picojson::array>();
        
        for (picojson::array::iterator i = ids.begin(); i != ids.end(); i++) {
            retweeters[counter++] = (int64_t)(*i).get<double>();
        }
        
        param["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return retweeters;
}

