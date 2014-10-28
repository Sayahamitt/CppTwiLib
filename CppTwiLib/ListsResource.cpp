//
//  ListsResource.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/19.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "ListsResource.h"

ListsResource::ListsResource(std::string c_key, std::string c_sec):TwitterAPIUser(c_key, c_sec){
    APIRESOURCENAME = "lists";
}

ListsResource::ListsResource(std::string c_key,std::string c_sec, std::string token, std::string token_sec):TwitterAPIUser(c_key,c_sec,token, token_sec){
    APIRESOURCENAME = "lists";
}

ListsResource::ListsResource(Twiauth certifyer):TwitterAPIUser(certifyer){
    APIRESOURCENAME = "lists";
}

std::vector<list> ListsResource::lists(std::map<std::string, std::string> paramaters){
    std::vector<list> listsarray;
    
    requesttoTwitter(GET, "list.json",paramaters);
    
    createObjectsArray(listsarray);
    return listsarray;
}

std::vector<list> ListsResource::lists(std::string userID){
    std::map<std::string, std::string> paramaters;
    std::vector<list> listsarray;
    
    paramaters["user_id"] = userID;
    
    requesttoTwitter(GET, "list.json",paramaters);
    
    createObjectsArray(listsarray);
    return listsarray;
}

std::vector<tweet> ListsResource::statuses(std::string listID,std::map<std::string, std::string> paramaters){
    std::vector<tweet> timeline;
    
    paramaters["list_id"]=listID;
    
    requesttoTwitter(GET, "statuses.json",paramaters);
    
    createObjectsArray(timeline);
    
    return timeline;
}

void ListsResource::members_destroy(std::string listID, std::string userID){
    std::map<std::string, std::string> paramaters;
    
    paramaters["list_id"]=listID;
    paramaters["user_id"]=userID;
    
    requesttoTwitter(POST, "members/destroy.json",paramaters);
    //std::cout<<getRawResponse()<<std::endl;
}

std::vector<list> ListsResource::memberships(std::map<std::string, std::string> paramaters){
    std::vector<list> listarray;
    picojson::array lists;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "memberships.json",paramaters);
        if (!response.is<picojson::object>()) {
            return listarray;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        lists = resObj["lists"].get<picojson::array>();
        
        for (picojson::array::iterator i = lists.begin(); i != lists.end(); i++) {
            listarray[counter++] = (*i).get<picojson::object>();
        }
        
        paramaters["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return listarray;
}

std::vector<user> ListsResource::subscribers(std::map<std::string, std::string> paramaters){
    std::vector<user> userarray;
    picojson::array lists;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "subscribers.json",paramaters);
        if (!response.is<picojson::object>()) {
            return userarray;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        lists = resObj["lists"].get<picojson::array>();
        
        for (picojson::array::iterator i = lists.begin(); i != lists.end(); i++) {
            userarray[counter++] = (*i).get<picojson::object>();
        }
        
        paramaters["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return userarray;
}

void ListsResource::subscribers_destroy(std::string listID){
    std::map<std::string, std::string> paramaters;
    
    paramaters["list_id"]=listID;
    
    requesttoTwitter(POST, "subscribers/destroy.json",paramaters);
}

list ListsResource::subscribers_create(std::string listID){
    std::map<std::string, std::string> paramaters;
    list tergetlist;
    
    paramaters["list_id"]=listID;
    
    requesttoTwitter(POST, "subscribers/create.json",paramaters);
    
    if(response.is<picojson::object>()){
        tergetlist = list(response.get<picojson::object>());
    }
    return tergetlist;
}

user ListsResource::subscribers_show(std::string listID, std::string userID){
    std::map<std::string, std::string> paramaters;
    user subscriber;
    
    paramaters["list_id"]=listID;
    paramaters["user_id"]=userID;
    
    requesttoTwitter(GET, "subscribers/show.json",paramaters);
    if(response.is<picojson::object>()){
        subscriber = user(response.get<picojson::object>());
    }
    return subscriber;
}

void ListsResource::members_create_all(std::string listID, std::vector<std::string> userIDarray){
    std::map<std::string, std::string> parameters;
    std::string unitedlist;
    
    for (std::vector<std::string>::iterator i=userIDarray.begin(); i != userIDarray.end(); i++) {
        unitedlist += (*i)+",";
    }unitedlist.erase(unitedlist.end()-1);
    
    parameters["screen_name"]=unitedlist;
    
    requesttoTwitter(POST,"members/create_all.json", parameters);
}

bool ListsResource::members_show(std::string listID, std::string userID){
    std::map<std::string, std::string> paramaters;
    user subscriber;
    std::string name;
    bool res = false;
    
    paramaters["list_id"]=listID;
    paramaters["user_id"]=userID;
    
    requesttoTwitter(GET, "subscribers/show.json",paramaters);
    if(response.is<picojson::object>()){
        subscriber = user(response.get<picojson::object>());
        res = subscriber.getScreenName(name);
    }
    return res;
}


std::vector<user> ListsResource::members(std::string listID){
    std::map<std::string, std::string> paramaters;
    std::vector<user> userarray;
    picojson::array lists;
    
    paramaters["list_id"] = listID;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "members.json",paramaters);
        if (!response.is<picojson::object>()) {
            return userarray;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        lists = resObj["lists"].get<picojson::array>();
        
        for (picojson::array::iterator i = lists.begin(); i != lists.end(); i++) {
            userarray[counter++] = (*i).get<picojson::object>();
        }
        
        paramaters["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return userarray;
}

void ListsResource::members_create(std::string listID, std::string userID){
    std::map<std::string, std::string> paramaters;
    
    paramaters["list_id"]=listID;
    paramaters["user_id"]=userID;
    
    requesttoTwitter(POST, "members/create.json",paramaters);
}

list ListsResource::destory(std::string listID){
    std::map<std::string, std::string> paramaters;
    list destoryed;
    
    paramaters["list_id"]=listID;
    
    requesttoTwitter(POST, "destroy.json",paramaters);
    if(response.is<picojson::object>()){
        destoryed = list(response.get<picojson::object>());
    }
    
    return destoryed;
}

void ListsResource::update(std::map<std::string, std::string> paramaters){
    list posted;
    
    requesttoTwitter(POST, "update.json",paramaters);
    if(response.is<picojson::object>()){
        posted = list(response.get<picojson::object>());
    }
}

list ListsResource::create(std::string name, std::map<std::string, std::string> paramaters){
    list created;
    
    paramaters["name"]=name;
    
    requesttoTwitter(POST, "create.json",paramaters);
    if(response.is<picojson::object>()){
        created = list(response.get<picojson::object>());
    }
    
    return created;
}

list ListsResource::show(std::string listID){
    std::map<std::string, std::string> paramaters;
    list terget;
    
    paramaters["list_id"]=listID;
    
    requesttoTwitter(POST, "show.json",paramaters);
    if(response.is<picojson::object>()){
        terget = list(response.get<picojson::object>());
    }
    
    return terget;
}

std::vector<list> ListsResource::subscriptions(std::string userID){
    std::map<std::string, std::string> paramaters;
    std::vector<list> listsarray;
    picojson::array lists;
    
    paramaters["user_id"] = userID;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "subscriptions.json",paramaters);
        if (!response.is<picojson::object>()) {
            return listsarray;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        lists = resObj["lists"].get<picojson::array>();
        
        for (picojson::array::iterator i = lists.begin(); i != lists.end(); i++) {
            listsarray[counter++] = (*i).get<picojson::object>();
        }
        
        paramaters["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return listsarray;
}

void ListsResource::members_destroy_all(std::string listID, std::vector<std::string> userIDarray){
    std::map<std::string, std::string> parameters;
    std::string unitedlist;
    
    for (std::vector<std::string>::iterator i=userIDarray.begin(); i != userIDarray.end(); i++) {
        unitedlist += (*i)+",";
    }unitedlist.erase(unitedlist.end()-1);
    
    parameters["screen_name"]=unitedlist;
    
    requesttoTwitter(POST,"members/destory_all.json", parameters);
}

std::vector<list> ListsResource::ownerships(std::string userID){
    std::map<std::string, std::string> paramaters;
    std::vector<list> listsarray;
    picojson::array lists;
    
    paramaters["user_id"] = userID;
    
    std::string nextCoursor;
    int counter=0;
    do{
        requesttoTwitter(GET, "ownerships.json",paramaters);
        if (!response.is<picojson::object>()) {
            return listsarray;
        }
        
        picojson::object resObj = response.get<picojson::object>();
        nextCoursor = resObj["previous_cursor_str"].get<std::string>();
        
        lists = resObj["lists"].get<picojson::array>();
        
        for (picojson::array::iterator i = lists.begin(); i != lists.end(); i++) {
            listsarray[counter++] = (*i).get<picojson::object>();
        }
        
        paramaters["cursor"]=nextCoursor;
    }while (nextCoursor != "0");
    
    return listsarray;
}