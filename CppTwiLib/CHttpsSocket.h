//
//  CHttpsSocket.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__CHttpsSocket__
#define __CppTwiLib__CHttpsSocket__

#include <iostream>
#include <sstream>
#include <string>
#include "openssl/ssl.h"

class HttpsSocket{
private:
    std::string HostNname;
    
    std::string ResponseString;
    std::string ResponseBody;
    unsigned int ResponeCode;
public:
    HttpsSocket(std::string inHost, std::string& requestHeader);
    HttpsSocket(HttpsSocket& obj);
    ~HttpsSocket();
    
    HttpsSocket& operator=(const HttpsSocket& rhs);
    
    std::string getResponsebody();
    unsigned int getResponeCode();
    
private:
    std::string https_socket(std::string& request_str);
    std::string https_body(std::string& request_str);
};
#endif /* defined(__CppTwiLib__CHttpsSocket__) */
