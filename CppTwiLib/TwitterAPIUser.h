#ifndef TwitterAPIUser_H
#define TwitterAPIUser_H

#include <string>
#include <vector>

#include "macros.h"

#include "Twiauth.h"
#include "TwitterException.h"
#include "CHttpsSocket.h"
#include "../picojson.h"

#include "user.h"
#include "tweet.h"
#include "errors.h"

class TwitterAPIUser{
protected:
    const Twiauth auth_header;
    std::string OwnerAccountname;
    
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
    TwitterAPIUser(const std::string& c_key, const std::string& c_sec);
    TwitterAPIUser(const std::string& c_key, const std::string& c_sec,
              const std::string& token, const std::string& token_sec);
    TwitterAPIUser(const std::string& ownername,const std::string& c_key, const std::string& c_sec,const std::string& token, const std::string& token_sec);
    TwitterAPIUser(const Twiauth& certifyer);
    virtual ~TwitterAPIUser();
    
    void showWhomResource();
    std::string isWhomResource();
    std::string isWhomResource() const;
    std::string getRawResponse() const;
    picojson::value getPicojsonResponse() const;
    
    void debug();
    
protected:
    std::string StringtoURLencode(const std::string& PlainString) const;
    std::string requesttoTwitter(const HttpMethod& method,const std::string& APINAME);
    std::string requesttoTwitter(const HttpMethod& method,const std::string& APINAME,
                                 const std::map<std::string, std::string>& parameters);
    template<typename TYPE>
    bool createObjectsArray(std::vector<TYPE>& destination) const{
        bool state = true;
        if (response.is<picojson::array>()){
            const picojson::array& picoTL = response.get<picojson::array>();
            
            for (picojson::array::const_iterator i = picoTL.begin(); i != picoTL.end(); i++) {
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