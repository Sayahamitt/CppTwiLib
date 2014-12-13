//
//  CHttpsSocket.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/09.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "CHttpsSocket.h"
#include <cstdlib>

//OpenSSLライブラリの関数群がXcodeでは非推奨となっている為、大量の警告が出るのを抑制
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

HttpsSocket::HttpsSocket(std::string inHost, std::string& requestHeader){
    HostNname = inHost;
    https_body(requestHeader);
}

HttpsSocket::HttpsSocket(HttpsSocket& obj){
    this->HostNname = obj.HostNname;
    this->ResponseString = obj.ResponseString;
    this->ResponseBody = obj.ResponseBody;
    this->ResponeCode = obj.ResponeCode;
}

HttpsSocket& HttpsSocket::operator=(const HttpsSocket& rhs){
    this->HostNname = rhs.HostNname;
    this->ResponseString = rhs.ResponseString;
    this->ResponseBody = rhs.ResponseBody;
    this->ResponeCode = rhs.ResponeCode;
    
    return *this;
}

HttpsSocket::~HttpsSocket(){}

std::string HttpsSocket::https_socket(std::string& request_str){
    BIO* bio;
    SSL* ssl;
    SSL_CTX* ctx;
    
    std::string buffer;
    
    int p;
    std::string host_and_protocol = HostNname+":https";
    char r[1024];
    
    SSL_library_init();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    ctx = SSL_CTX_new(SSLv23_client_method());
    bio = BIO_new_ssl_connect(ctx);
    
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    
    //std::cout<<host_and_protocol<<std::endl;
    
    BIO_set_conn_hostname(bio, host_and_protocol.c_str());
    
    if(BIO_do_connect(bio) <= 0){
        std::cout<<"BIO connection error"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    BIO_write(bio, request_str.c_str(),(int)request_str.size());
    
    while(1){
        p = BIO_read(bio, r, 1023);
        if(p <= 0) break;
        r[p] = 0;
        ResponseString += r;
    }
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    
    
    //<HTTPステータスコードの抽出>
    size_t endofline = ResponseString.find("\r\n",0);
    std::string firstline = ResponseString.substr(0,endofline);
    
    size_t codeBegin = firstline.find_last_of("HTTP/1.1 ",0) + sizeof("HTTP/1.1 ") -1;
    size_t codeEnd = firstline.find(" ",codeBegin) -1;
    size_t codeLength = codeEnd - codeBegin + 1;
    
    std::string codeStr = firstline.substr(codeBegin, codeLength);
    
    ResponeCode = atoi(codeStr.c_str());
    //</HTTPステータスコードの抽出>
    
    //std::cout<<ResponeCode<<std::endl;
    return ResponseString;
}

std::string HttpsSocket::https_body(std::string& request_str){
    std::string hole_data;
    std::string body;
    unsigned long copy_pos=0;
    
    hole_data = https_socket(request_str);
    
    copy_pos = hole_data.find("\r\n\r\n",0) + 4;
    if(copy_pos == std::string::npos){
        std::cout<<"HTTP BAD RESPONSE"<<std::endl;
    }
    ResponseBody = hole_data.substr(copy_pos);
    
    return ResponseBody;
}

std::string HttpsSocket::getResponsebody(){
    return ResponseBody;
}

unsigned int HttpsSocket::getResponeCode(){
    return ResponeCode;
}