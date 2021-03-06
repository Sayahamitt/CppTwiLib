#include <iostream>
#include <vector>

#include "Twiauth.h"
#include "TwitterAPIUser.h"
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
void MediaPostTest();

int main(){
    //UserTest();
    //StatusTest();
    MediaPostTest();
    //AuthTest();
    //APITest();
    return 0;
}

void ListsTest(){
    std::map<std::string,std::string> param;
    std::vector<std::string> namelist;
    ListsResource listapi(c_key,c_sec,my_access_token,my_access_sec);
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

void MediaPostTest(){
    StatusResource statusapi(c_key,c_sec,my_access_token,my_access_sec);
    
    statusapi.postImagetoTwitter("/Volumes/Working Data/Gentle Sheep/CppTwiLib/testmedia-s.png", "test-a");
    std::cout<<statusapi.getRawResponse()<<std::endl;
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
    std::string mypost_id;
    //param["count"]="200";
    
    timeline = statusapi.hometimeline(param);
    
    //std::cout<<statusapi.getRawResponse()<<std::endl;
    //mypost = statusapi.update_with_media("media upload のてすと", "/Volumes/Working Data/Gentle Sheep/CppTwiLib/testmedia.png");
    
    for (std::vector<tweet>::iterator i = timeline.begin(); i != timeline.end(); i++) {
        std::vector<std::string> usermentions;
        std::vector<std::string> hashtags;
        std::vector<std::string> urls;
        std::vector<std::string> medisurls;
        std::vector<std::string> retweeters;
        
        tweet rtstatus;
        
        (*i).getUser(account);
        account.getName(name);
        (*i).getText(status);
        (*i).getIDstr(mypost_id);
        
        (*i).getUserMentions(usermentions);
        (*i).getHashtags(hashtags);
        (*i).getUrls(urls);
        (*i).getMediaUrls(medisurls);
        
        
        std::cout<<name<<":"<<status<<std::endl;
        std::cout<<"TweetID:"<<mypost_id<<std::endl;
        
        for (std::vector<std::string>::iterator i = usermentions.begin(); i != usermentions.end(); i++) {
            std::cout<<"Mention to:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = hashtags.begin(); i != hashtags.end(); i++) {
            std::cout<<"hashtag:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = urls.begin(); i != urls.end(); i++) {
            std::cout<<"URL:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = medisurls.begin(); i != medisurls.end(); i++) {
            std::cout<<"MediaURL:"<<(*i)<<std::endl;
        }
        
        if ((*i).getRetweetedStatus(rtstatus)) {
            rtstatus.getIDstr(mypost_id);
            retweeters = statusapi.retweeters_ids(mypost_id);
            
            std::cout<<"RetweetersID:"<<std::flush;
            for (std::vector<std::string>::iterator i = retweeters.begin(); i != retweeters.end(); i++) {
                std::cout<<(*i)<<", "<<std::flush;
            }
            std::cout<<std::endl;
        }
        
        std::cout<<"-------------------------"<<std::endl;
    }
    
    //timeline[1].getID(mypost_id);
    //statusapi.retweet_id(mypost_id);
    
    //std::cout<<statusapi.retweeters_ids(mypost_id)[0]<<std::endl;
    
     std::string poststr;
     std::cout<<"ツイートを入力してください"<<std::endl;
     std::cin>>poststr;
     mypost = statusapi.update(poststr);
     mypost.getIDstr(mypost_id);
     mypost.getText(status);
     std::cout<<mypost_id<<std::endl;
     std::cout<<status<<std::endl;
     myshowing = statusapi.show_id(mypost_id, param);
     myshowing.getText(status);
     std::cout<<"showing : "<<status<<std::endl;
     std::cin>>name;
     statusapi.destory_id(mypost_id);
    
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
    
    
    StatusResource statusapi(certifyer);
    
    tweet mypost;
    tweet myshowing;
    std::string mypost_id;
    //param["count"]="200";
    
    timeline = statusapi.hometimeline(param);
    
    for (std::vector<tweet>::iterator i = timeline.begin(); i != timeline.end(); i++) {
        std::vector<std::string> usermentions;
        std::vector<std::string> hashtags;
        std::vector<std::string> urls;
        std::vector<std::string> medisurls;
        std::vector<std::string> retweeters;
        
        tweet rtstatus;
        
        (*i).getUser(account);
        account.getName(name);
        (*i).getText(statusdata);
        (*i).getIDstr(mypost_id);
        
        (*i).getUserMentions(usermentions);
        (*i).getHashtags(hashtags);
        (*i).getUrls(urls);
        (*i).getMediaUrls(medisurls);
        
        
        std::cout<<name<<":"<<statusdata<<std::endl;
        std::cout<<"TweetID:"<<mypost_id<<std::endl;
        
        for (std::vector<std::string>::iterator i = usermentions.begin(); i != usermentions.end(); i++) {
            std::cout<<"Mention to:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = hashtags.begin(); i != hashtags.end(); i++) {
            std::cout<<"hashtag:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = urls.begin(); i != urls.end(); i++) {
            std::cout<<"URL:"<<(*i)<<std::endl;
        }
        
        for (std::vector<std::string>::iterator i = medisurls.begin(); i != medisurls.end(); i++) {
            std::cout<<"MediaURL:"<<(*i)<<std::endl;
        }
        
        if ((*i).getRetweetedStatus(rtstatus)) {
            rtstatus.getIDstr(mypost_id);
            retweeters = statusapi.retweeters_ids(mypost_id);
            
            std::cout<<"RetweetersID:"<<std::flush;
            for (std::vector<std::string>::iterator i = retweeters.begin(); i != retweeters.end(); i++) {
                std::cout<<(*i)<<", "<<std::flush;
            }
            std::cout<<std::endl;
        }
        
        std::cout<<"-------------------------"<<std::endl;
    }
    /*
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
     
    */
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