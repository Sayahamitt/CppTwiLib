#ifndef TWITTERCLIENT_H
#define TWITTERCLIENT_H

#include <string>
#include <stdexcept>
#include "stringparams.h"

class Twiauth{
    
private:
    const static std::string request_token_url;
    const static std::string authorize_url;
    const static std::string access_token_url;
    
    const static std::string c_key_key;
    const static std::string nonce_key;
    const static std::string sig_method_key;
    const static std::string signature_key;
    const static std::string timestamp_key;
    const static std::string oauth_version_key;
    const static std::string verifier_key;
    const static std::string token_key;
    
    const static std::string sig_method;
    const static std::string oauth_version;
    const std::string c_key;
    const std::string c_sec;
    
    std::string request_token;
    std::string request_token_sec;
    std::string access_token;
    std::string access_token_sec;
    
    std::string m_user_id;
    std::string m_screen_name;
    
    enum api_method_type{
        n_get,
        n_post,
        n_delete,
        n_put,
        n_head,
        n_request,
        n_access
    };
    
    std::string create_header(const api_method_type& method,const std::string& url, stringparams& params) const;
    std::string Extractformbody(const std::string& holestring,const std::string& key) const;
    
    bool isempty;
    
public:
    
    Twiauth(const std::string& a_c_key,const std::string& a_c_sec,const std::string& token,const std::string& token_sec);
    Twiauth(const std::string& a_c_key, const std::string& a_c_sec);
    Twiauth(const Twiauth &obj);
    Twiauth();
    ~Twiauth();
    
    Twiauth& operator=(const Twiauth& left);
    
    bool empty() const;
    
    void debug() const;
    
    std::string get_authorize_url();
    bool set_access_token(const std::string& pin);
    
    std::string getAccessToken() const;
    std::string getAccessTokenSecret() const;
    
    std::string header_get(const std::string& url,stringparams& params) const;
    std::string header_post(const std::string& url,stringparams& params) const;
    //std::string header_delete(std::string url);
    //std::string header_put(std::string url);
    //std::string header_head(std::string url);
    
};

#endif
