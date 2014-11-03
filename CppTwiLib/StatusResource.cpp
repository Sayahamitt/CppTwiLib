//
//  StatusResource.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "StatusResource.h"

#include <sstream>

StatusResource::StatusResource(std::string c_key, std::string c_sec):TwitterAPIUser(c_key, c_sec){
    APIRESOURCENAME = "statuses";
}

StatusResource::StatusResource(std::string c_key,std::string c_sec, std::string token, std::string token_sec):TwitterAPIUser(c_key,c_sec,token, token_sec){
    APIRESOURCENAME = "statuses";
}

StatusResource::StatusResource(Twiauth certifyer):TwitterAPIUser(certifyer){
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

std::vector<tweet> StatusResource::user_timeline(std::string screenname){
    std::map<std::string,std::string> paramaters;
    return user_timeline(screenname, paramaters);
}

std::vector<tweet> StatusResource::user_timeline(std::map<std::string,std::string> paramaters){
    return user_timeline("", paramaters);
}

std::vector<tweet> StatusResource::retweets_of_me(std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    
    requesttoTwitter(GET,"retweets_of_me.json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}

std::vector<tweet> StatusResource::retweets_id(std::string tweetID,std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    
    paramaters.erase("id");
    
    requesttoTwitter(GET,"retweets/"+tweetID+".json", paramaters);
    
    createObjectsArray(timeline);
    return timeline;
}

std::vector<tweet> StatusResource::retweets_id(std::string tweetID){
    std::map<std::string,std::string> paramaters;
    return retweets_id(tweetID, paramaters);
}


tweet StatusResource::show_id(std::string tweetID,std::map<std::string, std::string> paramaters){
    tweet status;
    
    paramaters["id"]=tweetID;
    
    requesttoTwitter(GET, "show.json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

tweet StatusResource::show_id(std::string tweetID){
    std::map<std::string, std::string> paramaters;
    return show_id(tweetID, paramaters);
}

tweet StatusResource::destory_id(std::string tweetID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=tweetID;
    
    requesttoTwitter(POST, "destroy/"+tweetID+".json",paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

tweet StatusResource::update(std::string status){
    std::map<std::string, std::string> param;
    std::string http_header;
    tweet posted;
    
    status = StringtoURLencode(status);
    param["status"]=status;
    
    http_header = requesttoTwitter(POST, "update.json", param);
    
    if (response.is<picojson::object>()){
        posted = tweet(response.get<picojson::object>());
    }
    
    return posted;
}

tweet StatusResource::retweet_id(std::string tweetID){
    std::map<std::string, std::string> paramaters;
    tweet status;
    
    paramaters["id"]=tweetID;
    
    requesttoTwitter(POST, "retweet/"+tweetID+".json", paramaters);
    
    if (response.is<picojson::object>()){
        status = tweet(response.get<picojson::object>());
    }
    return status;
}

std::vector<std::string> StatusResource::retweeters_ids(std::string tweetID){
    std::map<std::string, std::string> param;
    std::vector<std::string> retweeters;
    param["id"]=tweetID;
    
    std::string nextCoursor;
    do{
        requesttoTwitter(GET, "retweeters/ids.json",param);
        if (!response.is<picojson::object>()) {
            return retweeters;
        }
        picojson::object resObj = response.get<picojson::object>();
        if (resObj.count("previous_cursor_str") &
            resObj.count("ids") &
            resObj.count("next_cursor_str")) {
            return  retweeters;
        }
        nextCoursor = resObj["next_cursor_str"].get<std::string>();
        if (resObj["ids"].is<picojson::array>() == false) {
            return retweeters;
        }
        const picojson::array& ids = resObj["ids"].get<picojson::array>();
        
        for (picojson::array::const_iterator i = ids.begin(); ids.empty() == false && i != ids.end(); i++) {
            retweeters.push_back( (*i).get<std::string>() );
        }
        
        param["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return retweeters;
}

