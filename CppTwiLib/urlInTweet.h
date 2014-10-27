//
//  urlInTweet.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/09/26.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__urlInTweet__
#define __CppTwiLib__urlInTweet__

#include <string>

class urlInTweet{
protected:
    std::string display_url;
    std::string expanded_url;
    int indices[2];
    std::string url;
    
public:
    urlInTweet();
    ~urlInTweet();
};

#endif /* defined(__CppTwiLib__urlInTweet__) */
