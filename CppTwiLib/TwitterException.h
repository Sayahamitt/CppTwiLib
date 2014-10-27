//
//  TwitterException.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/14.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__TwitterException__
#define __CppTwiLib__TwitterException__

#include <stdexcept>

#include "objects.h"

class TwitterException: public std::runtime_error{
private:
    std::string Massage;
    unsigned int ErrorCode;
public:
    TwitterException(std::string massage, unsigned int error_code);
    ~TwitterException();
    unsigned int getErrorCode();
    std::string getErrorMassage();
};

#endif /* defined(__CppTwiLib__TwitterException__) */
