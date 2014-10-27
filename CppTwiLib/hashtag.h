//
//  hashtag.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/26.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__hashtag__
#define __CppTwiLib__hashtag__

#include <iostream>
#include <string>

class hashtag{
protected:
    int indices[2];
    std::string text;
public:
    hashtag();
    ~hashtag();
};

#endif /* defined(__CppTwiLib__hashtag__) */
