//
//  TwitterException.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/14.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "TwitterException.h"

TwitterException::TwitterException(std::string massage, unsigned int error_code):
std::runtime_error(massage){
    Massage = massage;
    ErrorCode = error_code;
}

TwitterException::~TwitterException(){}

unsigned int TwitterException::getErrorCode(){
    return ErrorCode;
}

std::string TwitterException::getErrorMassage(){
    return Massage;
}
