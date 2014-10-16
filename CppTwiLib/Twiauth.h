#ifndef TWITTERCLIENT_H
#define TWITTERCLIENT_H

#include <string>
#include <stdexcept>
#include "stringparams.h"

class Twiauth{

 private:
	const std::string request_token_url;
	const std::string authorize_url;
	const std::string access_token_url;
	
	const std::string c_key_key;
	const std::string nonce_key;
	const std::string sig_method_key;
	const std::string signature_key;
	const std::string timestamp_key;
	const std::string oauth_version_key;
    const std::string verifier_key;
	const std::string token_key;
	
    const std::string c_key;
	const std::string c_sec;
	const std::string sig_method;
	const std::string oauth_version;
	
	std::string nonce;
	std::string signature;
	std::string timestamp;
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
	
	std::string create_header(api_method_type method,std::string url,stringparams params);
	
 public:
	
	Twiauth(std::string a_c_key, std::string a_c_sec, std::string token,std::string token_sec);
    Twiauth(std::string a_c_key, std::string a_c_sec);
	~Twiauth();
    
    std::string get_authorize_url();
    bool set_access_token(std::string pin);
    
    std::string getAccessToken();
    std::string getAccessTokenSecret();

	std::string header_get(std::string url,stringparams params);
	std::string header_post(std::string url,stringparams params);
	//std::string header_delete(std::string url);
	//std::string header_put(std::string url);
	//std::string header_head(std::string url);
	
};

#endif
