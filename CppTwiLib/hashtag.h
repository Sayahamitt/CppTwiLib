//
//  hashtag.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/26.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
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
