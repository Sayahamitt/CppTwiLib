//
//  errors.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/14.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__errors__
#define __CppTwiLib__errors__

#include "objects.h"

class errors : public Objects{
private:
    unsigned int ErrorCode;
    std::string ErrorMassage;
public:
    errors(picojson::object response);
    errors(unsigned int ErrorCode, std::string ErrorMassage);
    errors();
    ~errors();
    
    bool getMassage(std::string& destination);
    bool getErrorCode(unsigned int& destination);
};
#endif /* defined(__CppTwiLib__errors__) */
