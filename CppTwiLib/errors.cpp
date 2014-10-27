//
//  errors.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/14.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "errors.h"

errors::errors(picojson::object response):Objects(response){}

errors::errors(unsigned int ErrorCode, std::string ErrorMassage){
    this->ErrorCode = ErrorCode;
    this->ErrorMassage = ErrorMassage;
    isempty = false;
}

errors::errors():Objects(){}

errors::~errors(){}

bool errors::getMassage(std::string& destination){
    return getValuefromResponse<std::string>("massage", destination);
}

bool errors::getErrorCode(unsigned int& destination){
    double temp;
    bool res;
    res = getValuefromResponse<double>("code", temp);
    destination = (unsigned int)temp;
    return res;
}