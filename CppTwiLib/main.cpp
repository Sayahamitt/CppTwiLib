#include <iostream>

#include "Twiauth.h"
#include "Twistream.h"
#include "UsersResource.h"
#include "StatusResource.h"
#include "user.h"

#include "stringparams.h"

#include "../keys.h"

void AuthTest();
void APITest();

int main(){
    AuthTest();
  return 0;
}

void AuthTest(){
    Twiauth certifyer(c_key,c_sec);
    std::string pincode;
    
    std::cout<<certifyer.get_authorize_url()<<std::endl;
    std::cout<<"表示されたURLにブラウザでアクセスし、認証を行って得られたPINコードを入力して下さい。"<<std::endl;
    std::cout<<"PIN code >"<<std::flush;
    std::cin>>pincode;
    
    while(!certifyer.set_access_token(pincode)){
        std::cout<<"トークンを取得出来ませんでした。PINを入力し直して下さい。"<<std::endl;
        std::cout<<"PIN code >"<<std::flush;
        std::cin>>pincode;
    }
    
    std::cout<<"AccessToken :"<<certifyer.getAccessToken()<<std::endl;
    std::cout<<"AccessTokenSecret :"<<certifyer.getAccessTokenSecret()<<std::endl;
}

void APITest(){
    std::map<std::string,std::string> param;
    
    
    //param["trim_user"]="true";
    //param["count"]="3";
    //param["consributor_details"]="true";
    
    param["screen_name"]="roki0gjm";
    UsersResource cltest(c_key,c_sec,my_access_token,my_access_sec);
    StatusResource posttest(c_key,c_sec,my_access_token,my_access_sec);
    //cltest.set_access_token_cui();
    //posttest.hometimeline(param);
    //std::cout<<"\n"<<std::endl;
    //posttest.hometimeline(param);
    user test;
    test = cltest.users_lookup(param);
    std::string temp;
    test.getScreenName(temp);
    std::cout<<temp<<std::endl;
    //cltest.showWhomStream();
    //posttest.user_timeline("_motchy__",param);
    //posttest.update("もっかいてすと");
    //stringparams para;
    //para.add("count","2");
    //para.add("since_id","14927799");
    //twcl.create_header(Twiauth::n_get,"https://api.twitter.com/1.1/statuses/home_timeline.json",para);
}