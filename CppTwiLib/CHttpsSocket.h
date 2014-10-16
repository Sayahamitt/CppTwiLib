//
//  CHttpsSocket.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/09.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
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
    std::string hostrequest;
public:
    HttpsSocket(std::string inHost);
    
    std::string https_socket(std::string request_str);
    std::string https_body(std::string request_str);
};
#endif /* defined(__CppTwiLib__CHttpsSocket__) */
