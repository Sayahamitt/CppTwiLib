#ifndef TWISTREAM_H
#define TWISTREAM_H

#include <string>

#include "Twiauth.h"
#include "httpssocket.h"
#include "TwitterException.h"
#include "../picojson.h"

#include "user.h"
#include "errors.h"

class Twistream{
protected:
    Twiauth auth_header;
    std::string OwnerAccount;
    
    std::string strResponse;
    picojson::value response;
    
    enum HttpMethod{
        GET,
        POST
    };
    
    const std::string APIPROTOCOL;
    const std::string APIDOMEINNAME;
    const std::string APIVERSION;
    std::string APIRESOURCENAME;
    
public:
    Twistream(std::string c_key, std::string c_sec);
    Twistream(std::string c_key, std::string c_sec,
              std::string token, std::string token_sec);
    Twistream(Twiauth certifyer);
    ~Twistream();
    
    std::string get_authorize_url();
    void set_access_token(std::string pin);
    
    void showWhomStream();
    std::string isWhomStream();
    std::string getRawResponse();
    
    void debug();
    
protected:
    std::string StringtoURLencode(std::string PlainString);
    std::string requesttoTwitter(HttpMethod method,std::string APINAME);
    std::string requesttoTwitter(HttpMethod method,std::string APINAME,
                                   std::map<std::string, std::string> parameters);
    void checkAPIError();
};


#endif