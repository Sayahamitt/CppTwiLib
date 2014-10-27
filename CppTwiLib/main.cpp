#include <iostream>
#include <vector>

#include "Twiauth.h"
#include "Twistream.h"
#include "UsersResource.h"
#include "StatusResource.h"
#include "ListsResource.h"
#include "user.h"

#include "stringparams.h"

#include "../keys.h"

void AuthTest();
void APITest();
void StatusTest();
void UserTest();
void ListsTest();
    
int main(){
    UserTest();
    //StatusTest();
    //AuthTest();
    //APITest();
  return 0;
}

void ListsTest(){
    std::map<std::string,std::string> param;
    std::vector<std::string> namelist;
    ListsResource listskh3s4hx35pwt8api(c_key,c_sec,my_access_token,my_access_sec);
}

void UserTest(){
    std::map<std::string,std::string> param;
    std::vector<std::string> namelist;
    UsersResource userapi(c_key,c_sec,my_access_token,my_access_sec);
    
    std::string name;
    std::string userIDstr;
    int follower;
    user account;
    
    namelist.push_back("roki0gjm");
    namelist.push_back("sayahamitt");
    namelist.push_back("_motchy__");
    std::vector<user> userlist = userapi.lookup(namelist);
    
    for (std::vector<user>::iterator i = userlist.begin(); i != userlist.end(); i++) {
        (*i).getName(name);
        (*i).getIDstr(userIDstr);
        
        std::cout<<name<<std::endl;
    }
    
    account = userapi.show_id(userIDstr, param);
    //std::cout<<userapi.getRawResponse()<<std::endl;
    account.getName(name);
    account.getFollowersCount(follower);
    
    std::cout<<name<<" さんのフォロワー数:"<<follower<<"人"<<std::endl;
    
    
}

void StatusTest(){
    std::map<std::string,std::string> param;
    StatusResource statusapi(c_key,c_sec,my_access_token,my_access_sec);
    std::vector<tweet> timeline;
    user account;
    std::string name;
    std::string status;
    tweet mypost;
    tweet myshowing;
    int64_t mypost_id;

    //param["count"]="200";

    timeline = statusapi.user_timeline("_motchy__", param);
    
    for (std::vector<tweet>::iterator i = timeline.begin(); i != timeline.end(); i++) {
        (*i).getUser(account);
        account.getName(name);
        (*i).getText(status);
        (*i).getID(mypost_id);
        
        std::cout<<name<<":"<<status<<std::endl;
        std::cout<<mypost_id<<std::endl;
    }
    timeline[0].getID(mypost_id);
    statusapi.retweet_id(mypost_id);
    /*
    std::string poststr;
    std::cout<<"ツイートを入力してください"<<std::endl;
    std::cin>>poststr;
    mypost = statusapi.update(poststr);
    mypost.getID(mypost_id);
    mypost.getText(status);
    std::cout<<mypost_id<<std::endl;
    std::cout<<status<<std::endl;
    myshowing = statusapi.show_id(mypost_id, param);
    myshowing.getText(status);
    std::cout<<"showing : "<<status<<std::endl;
    std::cin>>name;
    statusapi.destory_id(mypost_id);
     */
}

void AuthTest(){
    std::map<std::string,std::string> param;
    
    std::vector<tweet> timeline;
    user account;
    std::string name;
    std::string statusdata;
    
    
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
    
    StatusResource status(certifyer);
    //status.debug();
    //StatusResource status(c_key,c_sec,certifyer.getAccessToken(),certifyer.getAccessTokenSecret());
    
    std::string poststr;
    std::cout<<"ツイートを入力してください"<<std::endl;
    std::cin>>poststr;
    status.update(poststr);
    
    
    param["count"]="10";
    timeline = status.hometimeline(param);
    
    for (std::vector<tweet>::iterator i = timeline.begin(); i != timeline.end(); i++) {
        (*i).getUser(account);
        account.getName(name);
        (*i).getText(statusdata);
        
        std::cout<<name<<":"<<statusdata<<std::endl;
    }
}

void APITest(){
    std::map<std::string,std::string> param;
    std::map<std::string,std::string> Userparam;
    std::vector<tweet> timeline;
    user account;
    std::string name;
    std::string status;
    
    //param["trim_user"]="true";
    param["count"]="3";
    param["consributor_details"]="true";
    
    Userparam["screen_name"]="roki0gjm";
    UsersResource cltest(c_key,c_sec,my_access_token,my_access_sec);
    StatusResource posttest(c_key,c_sec,my_access_token,my_access_sec);
    //cltest.set_access_token_cui();
    //posttest.hometimeline(param);
    //std::cout<<"\n"<<std::endl;
    timeline = posttest.hometimeline(param);
    
    //std::cout<<posttest.getRawResponse()<<std::endl;
    
    for (std::vector<tweet>::iterator i = timeline.begin(); i != timeline.end(); i++) {
        (*i).getUser(account);
        account.getName(name);
        (*i).getText(status);
        
        std::cout<<name<<":"<<status<<std::endl;
    }
    
    //std::string temp;
    //test.getScreenName(temp);
    //std::cout<<temp<<std::endl;
    //cltest.showWhomStream();
    //posttest.user_timeline("_motchy__",param);
    //posttest.update("もっかいてすと");
    //stringparams para;
    //para.add("count","2");
    //para.add("since_id","14927799");
    //twcl.create_header(Twiauth::n_get,"https://api.twitter.com/1.1/statuses/home_timeline.json",para);
}