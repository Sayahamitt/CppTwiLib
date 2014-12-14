#include <iostream>
#include <sstream>
#include <fstream>

#include <cstdlib>
#include <ctime>

#include "urlencode.h"
#include "TwitterAPIUser.h"
#include "base64.h"


const std::string TwitterAPIUser::APIPROTOCOL = "https://";
const std::string TwitterAPIUser::APIDOMEINNAME = "api.twitter.com";
const std::string TwitterAPIUser::APIVERSION = "1.1";

TwitterAPIUser::TwitterAPIUser(const std::string& c_key, const std::string& c_sec):
auth_header(c_key,c_sec){
}

TwitterAPIUser::TwitterAPIUser(const std::string& c_key, const std::string& c_sec,
                               const std::string& token, const std::string& token_sec):
auth_header(c_key,c_sec,token,token_sec){
}

TwitterAPIUser::TwitterAPIUser(const std::string& ownername,const std::string& c_key, const std::string& c_sec,const std::string& token, const std::string& token_sec):
auth_header(c_key,c_sec,token,token_sec),
OwnerAccountname(ownername)
{
}

TwitterAPIUser::TwitterAPIUser(const Twiauth& certifyer):
auth_header(certifyer){
}

TwitterAPIUser::~TwitterAPIUser(){}

void TwitterAPIUser::showWhomResource(){
    if(!OwnerAccountname.empty()){
        std::cout<<OwnerAccountname<<std::endl;
    }else{
        std::cout<<isWhomResource()<<std::endl;
    }
}

std::string TwitterAPIUser::isWhomResource(){
    std::string http_header;
    std::string tempAPIRES = APIRESOURCENAME;
    
    if (!OwnerAccountname.empty()) {
        return  OwnerAccountname;
    }
    
    APIRESOURCENAME = "account";
    http_header = requesttoTwitter(GET, "settings.json");
    APIRESOURCENAME = tempAPIRES;
    
    
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

std::string TwitterAPIUser::isWhomResource() const{
    return OwnerAccountname;
}

std::string TwitterAPIUser::getRawResponse() const{
    return strResponse;
}

picojson::value TwitterAPIUser::getPicojsonResponse() const{
    return response;
}

std::string TwitterAPIUser::StringtoURLencode(const std::string& PlainString) const{
    return percentEnc(PlainString);
}

std::string TwitterAPIUser::requesttoTwitter(const HttpMethod& method,const std::string& APINAME){
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
    
    HttpsSocket socket("api.twitter.com",http_header);
    strResponse = socket.getResponsebody();
    
    //strResponse = https_body(http_header,"api.twitter.com");
    
    std::string err;
    picojson::parse(response, strResponse.begin(), strResponse.end(),&err);
    if (!err.empty()) {
        throw std::runtime_error(err);
    }
    
    //TwitterAPIからエラーが返ってきていないかチェック
    if (!(socket.getResponeCode() == 200)) {
        try {
            checkAPIError();
        } catch (const TwitterException &err) {
            throw ;
        }
    }
    
    return http_header;
}

std::string TwitterAPIUser::requesttoTwitter(const HttpMethod& method,const std::string& APINAME,const std::map<std::string, std::string>& parameters){
    std::string http_header;
    std::string url_param;
    std::string AuthHeader;
    stringparams param;
    
    std::string APIURL = APIPROTOCOL + APIDOMEINNAME + "/" + APIVERSION + "/" +APIRESOURCENAME + "/" + APINAME;
    
    for (std::map<std::string,std::string>::const_iterator itargparam = parameters.begin();
         itargparam != parameters.end();
         itargparam++) {
        if (method==GET) {
            param.add(itargparam->first, percentEnc(itargparam->second));
        }else if (method == POST){
            param.add(itargparam->first, itargparam->second);
        }
    }
    
    param.sort_by_key();
    url_param = param.comb_params_by("=", "&");
    
    //HTTPヘッダ作成
    if (method == GET) {
        http_header += "GET ";
        AuthHeader = auth_header.header_get(APIURL,param);
    }else if (method == POST){
        http_header += "POST ";
        AuthHeader = auth_header.header_post_www_form(APIURL,param);
    }
    http_header += "/" + APIVERSION + "/" + APIRESOURCENAME + "/" + APINAME + "?";
    http_header += url_param;
    http_header += " HTTP/1.1\r\nHost: " + APIDOMEINNAME +"\r\n";
    http_header += AuthHeader+
    "\r\nConnection: Close\r\n\r\n";
    
    //std::cout<<http_header<<std::endl;//for debug
    
    HttpsSocket socket("api.twitter.com",http_header);
    strResponse = socket.getResponsebody();
    
    //strResponse = https_body(http_header,"api.twitter.com");
    
    std::string strerr;
    picojson::parse(response, strResponse.begin(), strResponse.end(),&strerr);
    if (!strerr.empty()) {
        throw std::runtime_error(strerr);//picojsonパース失敗時例外
    }
    
    //std::cout<<getRawResponse()<<std::endl;//for debug
    
    //TwitterAPIからエラーが返ってきていないかチェック
    if (!(socket.getResponeCode() == 200)) {
        try {
            checkAPIError();
        } catch (const TwitterException &err) {
            throw ;
        }
    }
    
    return http_header;
}

void TwitterAPIUser::postImagetoTwitter(const std::string& filepath,const std::string& filename){
    std::string http_header;
    std::string url_param;
    std::string AuthHeader;
    stringparams param;
    stringparams damy;
    
    std::string APIURL = "https://upload.twitter.com/1.1/media/upload.json";
    
    char* _boundary = new char[33];
    time_t now_time;
    time(&now_time);
    srand((unsigned int)now_time);
    for(int i=0;i<33;i++){
        _boundary[i] = rand() % 25 + 97;//UTF-8専用
    }_boundary[32]=0;
    
    std::string bounary(_boundary);
    
    std::string http_body;
    size_t filesize = 0;
    
    //HTTPリクエスト作成
    //画像ファイルオープン
    std::fstream file;
    file.open((filepath), std::ios::in | std::ios::binary);
    if (! file.is_open()) {
        throw std::runtime_error("faild to open a file");
    }
    //ファイルサイズ計測
    file.seekg(0,std::fstream::beg);
    std::fstream::pos_type begin = file.tellg();
    file.seekg(0,std::fstream::end);
    std::fstream::pos_type end = file.tellg();
    filesize = end - begin;
    file.seekg(std::ios::beg);
    
    //HTTPボディ作成
    char* mediadata = new char[filesize];
    file.read(mediadata, filesize);
    //std::string datastr = base64_encode((unsigned char*)mediadata, (unsigned int)filesize);
    std::string datastr(mediadata,filesize);
    
    //http_body += "\r\nContent-Type: application/octet-stream\r\n";
    http_body += "--" + bounary +"\r\n";
    //http_body += "Content-Transfer-Encoding: base64\r\n";
    http_body += "Content-Disposition: form-data; name=\"media\"; filename=\""+ filename +"\"\r\nContent-Type: application/octet-stream\r\n\r\n" + datastr + "\r\n";
    http_body += "--" + bounary + "--\r\n";
    
    //http_body += datastr;
    //HTTPヘッダ作成
    AuthHeader = auth_header.header_post(APIURL,http_body);
    http_header += "POST ";
    http_header += "/1.1/media/upload.json";
    //http_header += url_param;
    http_header += " HTTP/1.1\r\n";
    //http_header += "Accept-Encoding: gzip;q=1.0,deflate;q=0.6,identity;q=0.3\r\nAccept: */*\r\n";
    http_header += "Content-Type: multipart/form-data, boundary=\"" + bounary + "\"\r\n";
    http_header += AuthHeader+"\r\n";
    http_header += "Connection: close\r\n";
    http_header += "Host: upload.twitter.com\r\n";
    //http_header += "Content-Type: image/png\r\n";
    //http_header += "Content-Transfer-Encoding: base64\r\n";
    http_header += "Content-Length: " + std::to_string(http_body.size()) + "\r\n\r\n";
    
    http_header.append(http_body);
    
    std::cout<<http_header<<std::endl;//for debug
    
    
    
    HttpsSocket socket("upload.twitter.com",http_header);
    strResponse = socket.getResponsebody();
    
    
    std::string strerr;
    picojson::parse(response, strResponse.begin(), strResponse.end(),&strerr);
    if (!strerr.empty()) {
        throw std::runtime_error(strerr);//picojsonパース失敗時例外
    }
    
    //std::cout<<getRawResponse()<<std::endl;//for debug
    
    //TwitterAPIからエラーが返ってきていないかチェック
    if (!(socket.getResponeCode() == 200)) {
        try {
            checkAPIError();
        } catch (const TwitterException &err) {
            throw ;
        }
    }
}

void TwitterAPIUser::checkAPIError(){
    //TwitterAPIがerrorを返した際に例外を投げる処理//
    if (response.is<picojson::object>()){
        picojson::object analyte = response.get<picojson::object>();
        if (analyte.count("errors") == 1) {
            std::string errormassage;
            unsigned int errorcode;
            
            if (analyte["errors"].is<picojson::array>()) {
                picojson::array& anaArray = analyte["errors"].get<picojson::array>();
                if((anaArray[0].get<picojson::object>()).count("message")&&
                   (anaArray[0].get<picojson::object>()).count("code")){
                    errormassage = (anaArray[0].get<picojson::object>())["message"].get<std::string>();
                    errorcode = (unsigned int)(anaArray[0].get<picojson::object>())["code"].get<double>();
                }else{
                    throw std::runtime_error("Twitter returned an unexpected error format.");
                    
                }
            }else if(analyte["errors"].is<picojson::object>()){
                throw std::runtime_error("Twitter returned an unexpected error format.");
            }
            
            TwitterException TwitterAPIError(errormassage, errorcode);
            throw TwitterAPIError;//TwitterAPIがエラーを返した時に投げる例外
        }
    }else{
        throw std::runtime_error("Twitter returned an unexpected error format.");
    }
}

void TwitterAPIUser::debug(){
    auth_header.debug();
}
