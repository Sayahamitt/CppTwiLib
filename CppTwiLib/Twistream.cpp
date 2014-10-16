#include <iostream>
#include <sstream>

#include "Twistream.h"

#include "urlencode.h"

Twistream::Twistream(std::string c_key, std::string c_sec):
auth_header(c_key,c_sec),
APIPROTOCOL("https://"),
APIDOMEINNAME("api.twitter.com"),
APIVERSION ("1.1"){
}

Twistream::Twistream(std::string c_key, std::string c_sec,
                     std::string token,std::string token_sec):
auth_header(c_key,c_sec,token,token_sec),
APIPROTOCOL("https://"),
APIDOMEINNAME("api.twitter.com"),
APIVERSION ("1.1"){
}

Twistream::Twistream(Twiauth certifyer):
APIPROTOCOL("https://"),
APIDOMEINNAME("api.twitter.com"),
APIVERSION ("1.1"),
auth_header(certifyer){
}

Twistream::~Twistream(){}

std::string Twistream::get_authorize_url(){
    return auth_header.get_authorize_url();
}

void Twistream::set_access_token(std::string pin){
    auth_header.set_access_token(pin);
}

void Twistream::showWhomStream(){
    if(!OwnerAccount.empty()){
        std::cout<<OwnerAccount<<std::endl;
    }else{
        std::cout<<isWhomStream()<<std::endl;
    }
}

std::string Twistream::isWhomStream(){
    std::string http_header;
    std::string tempAPIRES = APIRESOURCENAME;
    
    if (!OwnerAccount.empty()) {
        return  OwnerAccount;
    }
    
    APIRESOURCENAME = "account";
    http_header = requesttoTwitter(GET, "settings.json");
    APIRESOURCENAME = tempAPIRES;
    
    /*
    std::cout<<http_header<<std::endl;//for debug
    std::string buffer = https_body(http_header,"api.twitter.com");
    std::cout<<buffer<<std::endl;
    */
    
    picojson::object strip;
    
    if (response.is<picojson::array>()){
        picojson::array& timeline = response.get<picojson::array>();
        for (picojson::array::iterator i = timeline.begin(); i != timeline.end(); i++) {
            std::cout<<"\njson is array"<<std::endl;
            strip = (*i).get<picojson::object>();
        }
    }else{
        strip = response.get<picojson::object>();
    }
    
    return strip["screen_name"].get<std::string>();
}

std::string Twistream::getRawResponse(){
    return strResponse;
}

std::string Twistream::StringtoURLencode(std::string PlainString){
    return percentEnc(PlainString);
}

std::string Twistream::requesttoTwitter(HttpMethod method,std::string APINAME){
    std::string http_header;
    stringparams param;
    
    std::string APIURL = APIPROTOCOL + APIDOMEINNAME + "/" + APIVERSION + "/" +APIRESOURCENAME + "/" + APINAME;
    
    //HTTPヘッダ作成
    if (method == GET) {
        http_header += "GET ";
    }else if (method == POST){
        http_header += "POST ";
    }
    http_header += "/" + APIVERSION + "/" + APIRESOURCENAME + "/" + APINAME + "?";
    http_header += " HTTP/1.1\r\nHost: " + APIDOMEINNAME +"\r\n";
    http_header += auth_header.header_get(APIURL,param)+
    "\r\nConnection: Close\r\n\r\n";
    
    strResponse = https_body(http_header,"api.twitter.com");

    std::string err;
    picojson::parse(response, strResponse.begin(), strResponse.end(),&err);
    if (!err.empty()) {
        throw std::runtime_error(err);
    }
    
    //TwitterAPIからエラーが返ってきていないかチェック
    try {
        checkAPIError();
    } catch (const TwitterException &err) {
        throw ;
    }
    
    return http_header;
}

std::string Twistream::requesttoTwitter(HttpMethod method,std::string APINAME,
                                          std::map<std::string, std::string> parameters){
    std::string http_header;
    std::string url_param;
    std::string AuthHeader;
    stringparams param;
    
    std::string APIURL = APIPROTOCOL + APIDOMEINNAME + "/" + APIVERSION + "/" +APIRESOURCENAME + "/" + APINAME;
    
    for (std::map<std::string,std::string>::iterator itargparam =parameters.begin();
         itargparam != parameters.end();
         itargparam++) {
        param.add(itargparam->first, itargparam->second);
    }
    
    param.sort_by_key();
    url_param = param.comb_params_by("=", "&");
    
    //HTTPヘッダ作成
    if (method == GET) {
        http_header += "GET ";
        AuthHeader = auth_header.header_get(APIURL,param);
    }else if (method == POST){
        http_header += "POST ";
        AuthHeader = auth_header.header_post(APIURL,param);
    }
    http_header += "/" + APIVERSION + "/" + APIRESOURCENAME + "/" + APINAME + "?";
    http_header += url_param;
    http_header += " HTTP/1.1\r\nHost: " + APIDOMEINNAME +"\r\n";
    http_header += AuthHeader+
    "\r\nConnection: Close\r\n\r\n";
    
    //std::cout<<http_header<<std::endl;//for debug
    
    strResponse = https_body(http_header,"api.twitter.com");
    
    std::string strerr;
    picojson::parse(response, strResponse.begin(), strResponse.end(),&strerr);
    if (!strerr.empty()) {
        throw std::runtime_error(strerr);//picojsonパース失敗時例外
    }
    
    //std::cout<<getRawResponse()<<std::endl;//for debug
    
    //TwitterAPIからエラーが返ってきていないかチェック
    try {
        checkAPIError();
    } catch (const TwitterException &err) {
        throw ;
    }
    
    return http_header;
}

void Twistream::checkAPIError(){
    //TwitterAPIがerrorを返した際に例外を投げる処理//
    if (response.is<picojson::object>()){
        picojson::object analyte = response.get<picojson::object>();
        if (analyte.count("errors") == 1) {
            std::string errormassage;
            unsigned int errorcode;
            
            if (analyte["errors"].is<picojson::array>()) {
                picojson::array& anaArray = analyte["errors"].get<picojson::array>();
                if((anaArray[0].get<picojson::object>()).count("message")){
                    errormassage = (anaArray[0].get<picojson::object>())["message"].get<std::string>();
                }
                if((anaArray[0].get<picojson::object>()).count("code")){
                    errorcode = (unsigned int)(anaArray[0].get<picojson::object>())["code"].get<double>();
                }
            }else if(analyte["errors"].is<picojson::object>()){
                errormassage = analyte["message"].get<std::string>();
                errorcode = (unsigned int)analyte["code"].get<double>();
            }
            
            TwitterException TwitterAPIError(errormassage, errorcode);
            throw TwitterAPIError;//TwitterAPIがエラーを返した時に投げる例外
        }
    }
}

void Twistream::debug(){
    auth_header.debug();
}
