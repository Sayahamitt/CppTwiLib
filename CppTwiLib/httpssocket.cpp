#include <iostream>
#include <sstream>
#include <string>
#include "openssl/ssl.h"
#include "httpssocket.h"

//OpenSSLライブラリの関数群がXcodeでは非推奨となっている為に大量の警告が出るのを抑制
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

std::string https_socket(std::string request_str,std::string host){
    BIO* bio;
    SSL* ssl;
    SSL_CTX* ctx;
    
    std::string buffer;
    
    int p;
    std::string host_and_protocol = host+":https";
    char r[1024];
    
    SSL_library_init();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    ctx = SSL_CTX_new(SSLv23_client_method());
    bio = BIO_new_ssl_connect(ctx);
    
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    
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
        buffer += r;
    }
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    
    return buffer;
}

std::string https_body(std::string request_str,std::string host){
    std::string hole_data;
    std::string body;
    unsigned long copy_pos=0;
    
    hole_data = https_socket(request_str,host);
    
    copy_pos = hole_data.find("\r\n\r\n",0) + 4;
    if(copy_pos == std::string::npos){
        std::cout<<"HTTP BAD RESPONSE"<<std::endl;
    }
    body = hole_data.substr(copy_pos);
    
    return body;
}
