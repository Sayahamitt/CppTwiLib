//
//  FavoritesResource.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/19.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__FavoritesResource__
#define __CppTwiLib__FavoritesResource__

#include "Twistream.h"
#include "tweet.h"

class FavoritesResource : public Twistream{
public:
    FavoritesResource(std::string c_key, std::string c_sec);
    FavoritesResource(std::string c_key, std::string c_sec, std::string token, std::string token_sec);
    FavoritesResource(Twiauth certifyer);
    
    std::vector<tweet> list(std::map<std::string, std::string> paramaters);
    tweet destroy(int64_t statusID);
    tweet create(int64_t statusID);
};

#endif /* defined(__CppTwiLib__FavoritesResource__) */
