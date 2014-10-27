//
//  mention.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/26.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__mention__
#define __CppTwiLib__mention__

#include <string>

class mention{
protected:
    int64_t id;
    std::string id_str;
    int indices[2];
    std::string name;
    std::string screen_name;
    
public:
    mention();
    ~mention();
};

#endif /* defined(__CppTwiLib__mention__) */
