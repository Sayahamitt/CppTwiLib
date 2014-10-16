//
//  entities.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/22.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__entities__
#define __CppTwiLib__entities__

#include <iostream>
#include <vector>

#include "hashtag.h"
#include "mediaInTweet.h"
#include "urlInTweet.h"
#include "mention.h"

class entities{
protected:
    std::vector<hashtag> hashtags;
    std::vector<mediaInTweet> medias;
    std::vector<urlInTweet> urls;
    std::vector<mention> ReplySource;
    
public:
    entities();
    ~entities();
};

#endif /* defined(__CppTwiLib__entities__) */
