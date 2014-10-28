#ifndef TWISTREAM_H
#define TWISTREAM_H

#include <string>
#include <vector>

#include "Twiauth.h"
#include "TwitterException.h"
#include "CHttpsSocket.h"
#include "../picojson.h"

#include "user.h"
#include "tweet.h"
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
    
    const static std::string APIPROTOCOL;
    const static std::string APIDOMEINNAME;
    const static std::string APIVERSION;
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
    template<typename TYPE>
    bool createObjectsArray(std::vector<TYPE>& destination){
        bool state = true;
        if (response.is<picojson::array>()){
            picojson::array& picoTL = response.get<picojson::array>();
            
            for (picojson::array::iterator i = picoTL.begin(); i != picoTL.end(); i++) {
                if (!(*i).is<picojson::array>()) {
                    destination.push_back( (*i).get<picojson::object>() );
                }
                state = false;
            }
        }else if (response.is<picojson::object>()){
            destination.push_back(response.get<picojson::object>());
        }
        
        return state;
    }
    
    void checkAPIError();
};


#endif