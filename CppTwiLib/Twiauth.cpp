#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <openssl/ssl.h>

#include "base64.h"
#include "urlencode.h"
#include "httpssocket.h"

#include "CHttpsSocket.h"

#include "Twiauth.h"

//OpenSSLライブラリの関数群がXcodeでは非推奨となっている為に警告が出るのを抑制
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

const std::string Twiauth::request_token_url = "https://api.twitter.com/oauth/request_token";
const std::string Twiauth::authorize_url = "https://api.twitter.com/oauth/authorize";
const std::string Twiauth::access_token_url = "https://api.twitter.com/oauth/access_token";
const std::string Twiauth::c_key_key = "oauth_consumer_key";
const std::string Twiauth::nonce_key = "oauth_nonce";
const std::string Twiauth::sig_method_key = "oauth_signature_method";
const std::string Twiauth::signature_key = "oauth_signature";
const std::string Twiauth::timestamp_key = "oauth_timestamp";
const std::string Twiauth::verifier_key = "oauth_verifier";
const std::string Twiauth::oauth_version_key = "oauth_version";
const std::string Twiauth::token_key = "oauth_token";
const std::string Twiauth::sig_method = "HMAC-SHA1";
const std::string Twiauth::oauth_version = "1.0";

Twiauth::Twiauth(const std::string& a_c_key, const std::string& a_c_sec):
c_key(a_c_key),
c_sec(a_c_sec),
isempty(false)
{
}

Twiauth::Twiauth(const std::string& a_c_key,const std::string& a_c_sec,const std::string& token,const std::string& token_sec):
c_key(a_c_key),
c_sec(a_c_sec),
access_token(token),
access_token_sec(token_sec),
isempty(false)
{
}

Twiauth::Twiauth(const Twiauth &obj):
c_key(obj.c_key),
c_sec(obj.c_sec),
request_token(obj.request_token),
request_token_sec(obj.request_token_sec),
access_token(obj.access_token),
access_token_sec(obj.access_token_sec),
m_user_id(obj.m_user_id),
m_screen_name(obj.m_screen_name),
isempty(obj.isempty)
{
}

Twiauth::Twiauth():
isempty(true)
{
}

Twiauth::~Twiauth(){}

Twiauth& Twiauth::operator=(const Twiauth& left){
    this->request_token = left.request_token;
    this->request_token_sec = left.request_token_sec;
    this->access_token = left.access_token;
    this->access_token_sec = left.access_token_sec;
    this->m_user_id = left.m_user_id;
    this->m_screen_name = left.m_screen_name;
    this->isempty = left.isempty;
    
    return *this;
}

bool Twiauth::empty() const{
    return isempty;
}

std::string Twiauth::create_header(const api_method_type& method,const std::string& url, stringparams& params) const{
    stringparams oauth_params;
    std::string auth_header;
    std::string http_header;
    
    std::string api_url;
    
    time_t now_time;
    char co_nonce[33];
    std::stringstream out_stream;
    std::string sig_plain;
    
    std::string nonce;
    std::string signature;
    std::string timestamp;
    
    unsigned char co_signature[SHA_DIGEST_LENGTH];
    unsigned int co_siglen;
    
    //受け取ったパラメータに必須パラメータを追加
    oauth_params.add(c_key_key,c_key);
    oauth_params.add(sig_method_key,sig_method);
    oauth_params.add(oauth_version_key,oauth_version);
    if(method==access){
        oauth_params.add(token_key,request_token);
        oauth_params+=params;
    }else if(method == post){
        oauth_params+=params;
        oauth_params.add(token_key,access_token);
    }else if(method!=request){
        oauth_params.add(token_key,access_token);
    }
    
    //現在時刻取得,文字列化
    out_stream<<time(&now_time);
    timestamp=out_stream.str();
    
    oauth_params.add(timestamp_key, timestamp);//パラメータに追加
    out_stream.str("");
    
    //nonce生成,ランダムな英小文字32桁
    srand((unsigned int)now_time);
    for(int i=0;i<33;i++){
        co_nonce[i] = rand() % 25 + 97;//UTF-8専用
    }
    co_nonce[32]=0;
    nonce = co_nonce;
    
    oauth_params.add(nonce_key,nonce);//パラメータに追加
    
    //シグニチャ作成
    stringparams sig_params;
    sig_params += oauth_params;
    if(method != access && method != post){
        sig_params += params;
    }
    
    sig_params.sort_by_key();
    sig_plain = sig_params.comb_params_by("=","&");
    
    //シグネチャ生成用鍵の作成とapi_urlの設定
    std::string sig_key;
    
    if(method==access){
        sig_key = c_sec+"&"+request_token_sec;
        api_url = access_token_url;
    }else if(method==request){
        sig_key = c_sec+"&";
        api_url = request_token_url;
    }else{
        sig_key = c_sec+"&"+access_token_sec;
        api_url = url;
    }
    
    //メソッド指定子の決定
    std::string http_type;
    switch(method){
        case get:
            http_type = "GET";break;
        case request:
            http_type = "GET";break;
        case access:
            http_type = "GET";break;
        case post:
            http_type = "POST";break;
        case post_www_form:
            http_type = "POST";break;
        default:
            std::cout<<"HTTP method type is bad!! @Twiauth::crete_header"
            <<std::endl;
            break;
    }
    
    //std::cout<<http_type<<"&"<<request_token_url<<"&"<<sig_plain<<std::endl;//for debug
    
    sig_plain = http_type+"&"+percentEnc(api_url)+"&"+percentEnc(sig_plain);
    
    //std::cout<<sig_plain<<std::endl;//for debug
    
    //シグニチャ生成,OpenSSLのHMAC関数を利用
    HMAC(EVP_sha1(),sig_key.c_str(),(int)sig_key.length(),
         (unsigned char*)sig_plain.c_str(),sig_plain.size(),co_signature,&co_siglen);
    
    signature = base64_encode(co_signature, sizeof(co_signature));
    signature = percentEnc(signature);
    
    //std::cout<<signature<<std::endl;//for debug
    oauth_params.add(signature_key,signature);
    oauth_params.sort_by_key();
    
    //Authorizationヘッダ作成
    auth_header = "Authorization: OAuth "+
    oauth_params.comb_params_by("=\"","\", ")+"\"";
    
    return auth_header;
}

std::string Twiauth::header_get(const std::string& url,stringparams& params) const{
    return create_header(get,url,params);
}

std::string Twiauth::header_post_www_form(const std::string& url,stringparams& wwwFormDatas) const{
    return create_header(post_www_form,url,wwwFormDatas);
}

std::string Twiauth::header_post(const std::string &url, const std::string &postdata) const{
    stringparams params;
    unsigned char hash[SHA_DIGEST_LENGTH];
    
    SHA1((unsigned char*)postdata.c_str(),(unsigned long)postdata.size(),hash);
    std::string body_hash = base64_encode(hash,sizeof(hash));
    body_hash = percentEnc(body_hash);
    
    params.add("oauth_body_hash", body_hash);
    
    return create_header(post, url, params);
}

std::string Twiauth::Extractformbody(const std::string& holestring,const std::string& key) const{
    unsigned long pos_begin,pos_end;
    std::string KeywithEq = key + "=";
    std::string value;
    
    pos_begin = holestring.find(KeywithEq,0)+KeywithEq.length();
    pos_end = holestring.find("&",pos_begin);
    value = holestring.substr(pos_begin,pos_end - pos_begin);
    
    return value;
}

std::string Twiauth::get_authorize_url(){
    stringparams param;
    std::string http_header;
    std::string auth_header = create_header(request,request_token_url,param);
    std::string buffer;
    //---request_token取得---
    //HTTPヘッダ作成
    http_header = "GET /oauth/request_token HTTP/1.1\r\nHost: api.twitter.com\r\n"+
    auth_header+
    "\r\nConnection: Close\r\n\r\n";
    
    //std::cout<<http_header<<std::endl;//for debug
    
    HttpsSocket socket("api.twitter.com", http_header);
    
    //HTTPレスポンスコードが200以外だったら例外を投げる
    if (!(socket.getResponeCode() == 200)) {
        throw std::runtime_error("Could not obtain Authrization request token");
    }
    
    buffer = socket.getResponsebody();
    //std::cout<<buffer<<std::endl;
    
    //得られたhttpレスポンスのbodyからrequest_tokenとrequest_token_secを抽出
    //受信文字列に"auht_token="が含まれなかったら例外を投げる
    if (buffer.find("oauth_token=",0) == std::string::npos) {
        throw std::runtime_error("Could not obtain Authrization request token");
    }
    
    request_token = Extractformbody(buffer, "oauth_token");
    request_token_sec = Extractformbody(buffer, "oauth_token_secret");
    
    //std::cout<<request_token<<std::endl;//for debug
    //std::cout<<request_token_sec<<std::endl;//for debug
    
    return authorize_url+'?'+token_key+'='+request_token;
}

bool Twiauth::set_access_token(const std::string& pin){
    stringparams param;
    std::string http_header;
    std::string auth_header;
    std::string buffer;
    std::string verifier;
    
    //---access_token取得---
    //ブラウザ経由でユーザーに認証,PINコードを入力してもらう
    verifier = pin;
    //std::cout<<verifier<<std::endl;//for debug
    
    param.add(verifier_key,verifier);
    
    auth_header=create_header(access,access_token_url,param);
    
    //HTTPヘッダ作成
    http_header = "GET /oauth/access_token HTTP/1.1\r\nHost: api.twitter.com\r\n"+
    auth_header+
    "\r\nConnection: Close\r\n\r\n";
    
    //std::cout<<http_header<<std::endl;//for debug
    HttpsSocket socket("api.twitter.com", http_header);
    
    //HTTPレスポンスコードが200以外だったらfalseを返す
    if (!(socket.getResponeCode() == 200)) {
        return false;
    }
    
    buffer = socket.getResponsebody();
    //std::cout<<buffer<<std::endl;//for debug
    
    //得られたトークンとユーザー名の文字列を記録
    //得られたhttpレスポンスのbodyからaccess_tokenとaccess_token_secを抽出
    access_token = Extractformbody(buffer, "oauth_token");
    access_token_sec = Extractformbody(buffer, "oauth_token_secret");
    m_user_id = Extractformbody(buffer, "user_id");
    m_screen_name = Extractformbody(buffer, "screen_name");
    
    return true;
}

std::string Twiauth::getAccessToken() const{
    return access_token;
}

std::string Twiauth::getAccessTokenSecret() const{
    return access_token_sec;
}

void Twiauth::debug() const{
    std::cout<<c_key<<std::endl;
    std::cout<<c_sec<<std::endl;
    std::cout<<access_token<<std::endl;
    std::cout<<access_token_sec<<std::endl;
    
}