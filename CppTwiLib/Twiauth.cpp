#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <openssl/ssl.h>

#include "base64.h"
#include "urlencode.h"
#include "httpssocket.h"

#include "Twiauth.h"

//OpenSSLライブラリの関数群がXcodeでは非推奨となっている為に警告が出るのを抑制
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Twiauth::Twiauth(std::string a_c_key, std::string a_c_sec):
request_token_url("https://api.twitter.com/oauth/request_token"),
authorize_url("https://api.twitter.com/oauth/authorize"),
access_token_url("https://api.twitter.com/oauth/access_token"),
c_key_key("oauth_consumer_key"),
nonce_key("oauth_nonce"),
sig_method_key("oauth_signature_method"),
signature_key("oauth_signature"),
timestamp_key("oauth_timestamp"),
verifier_key("oauth_verifier"),
oauth_version_key("oauth_version"),
token_key("oauth_token"),
sig_method("HMAC-SHA1"),
oauth_version("1.0"),
c_key(a_c_key),
c_sec(a_c_sec)
{
    isempty = false;
}

Twiauth::Twiauth(std::string a_c_key, std::string a_c_sec, std::string token,std::string token_sec):
request_token_url("https://api.twitter.com/oauth/request_token"),
authorize_url("https://api.twitter.com/oauth/authorize"),
access_token_url("https://api.twitter.com/oauth/access_token"),
c_key_key("oauth_consumer_key"),
nonce_key("oauth_nonce"),
sig_method_key("oauth_signature_method"),
signature_key("oauth_signature"),
timestamp_key("oauth_timestamp"),
verifier_key("oauth_verifier"),
oauth_version_key("oauth_version"),
token_key("oauth_token"),
sig_method("HMAC-SHA1"),
oauth_version("1.0"),
c_key(a_c_key),
c_sec(a_c_sec)
{
    access_token = token;
    access_token_sec = token_sec;
    
    isempty = false;
}

Twiauth::Twiauth(const Twiauth &obj):
request_token_url("https://api.twitter.com/oauth/request_token"),
authorize_url("https://api.twitter.com/oauth/authorize"),
access_token_url("https://api.twitter.com/oauth/access_token"),
c_key_key("oauth_consumer_key"),
nonce_key("oauth_nonce"),
sig_method_key("oauth_signature_method"),
signature_key("oauth_signature"),
timestamp_key("oauth_timestamp"),
verifier_key("oauth_verifier"),
oauth_version_key("oauth_version"),
token_key("oauth_token"),
sig_method("HMAC-SHA1"),
oauth_version("1.0"),
c_key(obj.c_key),
c_sec(obj.c_sec)
{
    this->request_token = obj.request_token;
    this->request_token_sec = obj.request_token_sec;
    this->access_token = obj.access_token;
    this->access_token_sec = obj.access_token_sec;
    this->m_user_id = obj.m_user_id;
    this->m_screen_name = obj.m_screen_name;
    this->isempty = obj.isempty;
}

Twiauth::Twiauth(){
    isempty = true;
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

bool Twiauth::empty(){
    return isempty;
}

std::string Twiauth::create_header(api_method_type method,std::string url,stringparams params){
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
  if(method==n_access){
    oauth_params.add(token_key,request_token);
		oauth_params+=params;
  }else if(method!=n_request){
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
	params+=oauth_params;
	
  params.sort_by_key();
  sig_plain = params.comb_params_by("=","&");

  //シグネチャ生成用鍵の作成とapi_urlの設定
  std::string sig_key;
	
  if(method==n_access){
    sig_key = c_sec+"&"+request_token_sec;
    api_url = access_token_url;
  }else if(method==n_request){
    sig_key = c_sec+"&";
    api_url = request_token_url;
  }else{
    sig_key = c_sec+"&"+access_token_sec;
		api_url = url;
  }

  //メソッド指定子の決定
  std::string http_type;
  switch(method){
  case n_get:
    http_type = "GET";break;
  case n_request:
    http_type = "GET";break;
  case n_access:
    http_type = "GET";break;
  case n_post:
    http_type = "POST";break;
  case n_delete:
    http_type = "DELETE";break;
  case n_head:
    http_type = "HEAD";break;
  default:
    std::cout<<"HTTP method type is bad!! @Twiauth::crete_header"
	     <<std::endl;
    break;
  }

  //std::cout<<http_type<<"&"<<request_token_url<<"&"<<sig_plain<<std::endl;//for debug

  sig_plain = http_type+"&"+percentEnc(api_url)+"&"+percentEnc(sig_plain);

  //std::cout<<sig_plain<<std::endl;//for debug

	//シグニチャ生成,OpenSSLのHMAC関数を利用
  HMAC(EVP_sha1(),sig_key.c_str(),(int)sig_key.length(),(unsigned char*)sig_plain.c_str(),sig_plain.size(),
       co_signature,&co_siglen);

  signature = base64_encode(co_signature, sizeof(co_signature));
  signature = percentEnc(signature);

  //std::cout<<signature<<std::endl;//for debug
  oauth_params.add(signature_key,signature);
	oauth_params.sort_by_key();

  //Authorizationヘッダ作成
  auth_header = "Authorization: OAuth "+
    oauth_params.comb_params_by("=\"","\", ")+
    "\"";

  return auth_header;
}

std::string Twiauth::header_get(std::string url,stringparams params){
	return create_header(n_get,url,params);
}

std::string Twiauth::header_post(std::string url,stringparams params){
	return create_header(n_post,url,params);
}

std::string Twiauth::get_authorize_url(){
    stringparams param;
    std::string http_header;
    std::string auth_header = create_header(n_request,request_token_url,param);
    unsigned long pos_begin,pos_end;
    std::string buffer;
    //---request_token取得---
    //HTTPヘッダ作成
    http_header = "GET /oauth/request_token HTTP/1.1\r\nHost: api.twitter.com\r\n"+
    auth_header+
    "\r\nConnection: Close\r\n\r\n";
    
    //std::cout<<http_header<<std::endl;//for debug
    
    buffer = https_body(http_header,"api.twitter.com");
    //std::cout<<buffer<<std::endl;
    
    //得られたhttpレスポンスのbodyからrequest_tokenとrequest_token_secを抽出
    //受信文字列に"auht_token="が含まれなかったら例外を投げる
    if (buffer.find("oauth_token=",0) == std::string::npos) {
        throw std::runtime_error("Could not obtain Authrization request token");
    }
    
    pos_begin = buffer.find("oauth_token=",0)+sizeof("oauth_token=")-1;
    pos_end = buffer.find("&",0);
    request_token = buffer.substr(pos_begin,pos_end - pos_begin);
    pos_begin = buffer.find("oauth_token_secret=",0)+sizeof("oauth_token_secret=")-1;
    pos_end = buffer.find("&",pos_begin);
    request_token_sec = buffer.substr(pos_begin,pos_end - pos_begin);
    
    //std::cout<<request_token<<std::endl;//for debug
    //std::cout<<request_token_sec<<std::endl;//for debug
    
    return authorize_url+'?'+token_key+'='+request_token;
}

bool Twiauth::set_access_token(std::string pin){
    stringparams param;
	std::string http_header;
	std::string auth_header;
	unsigned long pos_begin,pos_end;
	std::string buffer;
	std::string verifier;
    
	//---access_token取得---
	//ブラウザ経由でユーザーに認証,PINコードを入力してもらう
    verifier = pin;
	//std::cout<<verifier<<std::endl;//for debug
    
	param.add(verifier_key,verifier);
    
	auth_header=create_header(n_access,access_token_url,param);
    
	//HTTPヘッダ作成
	http_header = "GET /oauth/access_token HTTP/1.1\r\nHost: api.twitter.com\r\n"+
    auth_header+
    "\r\nConnection: Close\r\n\r\n";
    
	//std::cout<<http_header<<std::endl;//for debug
    
	buffer = https_body(http_header,"api.twitter.com");
	//std::cout<<buffer<<std::endl;//for debug
    
	//得られたトークンとユーザー名の文字列を記録
    //得られたhttpレスポンスのbodyからaccess_tokenとaccess_token_secを抽出
    //受信文字列に"auht_token="が含まれなかったらfalseを返す
    if (buffer.find("oauth_token=",0) == std::string::npos) {
        return false;
    }
    
	pos_begin = buffer.find("oauth_token=",0)+sizeof("oauth_token=")-1;
	pos_end = buffer.find("&",0);
	access_token = buffer.substr(pos_begin,pos_end - pos_begin);
	pos_begin = buffer.find("oauth_token_secret=",0)+sizeof("oauth_token_secret=")-1;
	pos_end = buffer.find("&",pos_begin);
	access_token_sec = buffer.substr(pos_begin,pos_end - pos_begin);
	pos_begin = buffer.find("user_id=",0)+sizeof("user_id=")-1;
	pos_end = buffer.find("&",pos_begin);
	m_user_id = buffer.substr(pos_begin,pos_end - pos_begin);
	pos_begin = buffer.find("screen_name=",0)+sizeof("screen_name=")-1;
	pos_end = buffer.find("&",pos_begin);
	m_screen_name = buffer.substr(pos_begin,pos_end - pos_begin);
    
    return true;
}

std::string Twiauth::getAccessToken(){
    return access_token;
}

std::string Twiauth::getAccessTokenSecret(){
    return access_token_sec;
}

void Twiauth::debug(){
    std::cout<<c_key<<std::endl;
    std::cout<<c_sec<<std::endl;
    std::cout<<access_token<<std::endl;
    std::cout<<access_token_sec<<std::endl;
    
}