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
}

std::vector<tweet> StatusResource::hometimeline(std::map<std::string,std::string> paramaters){
    std::vector<tweet> timeline;
    std::string http_header;
    
    http_header = requesttoTwitter(GET,"home_timeline.json", paramaters);
    
    //std::cout<<http_header<<std::endl;//for debug
    //std::cout<<getRawResponse()<<std::endl;//for debug
    
    if (response.is<picojson::array>()){
        //std::cout<<"\njson is array"<<std::endl;for debug
        picojson::array& picoTL = response.get<picojson::array>();
        
        for (picojson::array::iterator i = picoTL.begin(); i != picoTL.end(); i++) {
            //std::cout<<"\njson is array"<<std::endl;  //for debug
            timeline.push_back( (*i).get<picojson::object>() );
        }
    }
    return timeline;
}


std::vector<tweet> StatusResource::user_timeline(std::string screenname,std::map<std::string, std::string> paramaters){
    std::vector<tweet> timeline;
    std::string http_header;
    
    paramaters["screen_name"]=screenname;
    
    http_header = requesttoTwitter(GET, "user_timeline.json",paramaters);
    
    picojson::object strip;
    
    if (response.is<picojson::array>()){
        picojson::array& picoTL = response.get<picojson::array>();
        
        for (picojson::array::iterator i = picoTL.begin(); i != picoTL.end(); i++) {
            timeline.push_back( (*i).get<picojson::object>() );
        }
    }
    return timeline;
}


tweet StatusResource::update(std::string poststr){
    std::map<std::string, std::string> param;
    std::string http_header;
    tweet posted;
    
    poststr = StringtoURLencode(poststr);
    param["status"]=poststr;
    
    http_header = requesttoTwitter(POST, "update.json", param);
    
    std::cout<<http_header<<std::endl;//for debug
    //std::cout<<"\n"+getRawResponse()<<std::endl;//for debug
    
    if (response.is<picojson::object>()){
        posted = tweet(response.get<picojson::object>());
    }
    
    return posted;
}
