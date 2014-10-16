//
//  mediaInTweet.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/09/26.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__mediaInTweet__
#define __CppTwiLib__mediaInTweet__

#include <string>
#include <vector>

class mediaInTweet{
protected:
    typedef struct sizeOfMedia{
        int h;
        int w;
        std::string resize;
    }sizeOfMedia;
protected:
    std::string display_url;
    std::string expanded_url;
    int64_t id;
    std::string id_str;
    int indices[2];
    std::string media_url;
    std::string media_url_https;
    std::vector<sizeOfMedia> sizes;
    int64_t source_status_id;
    std::string source_status_id_str;
    std::string mediaType;
    std::string mediaURL;
public:
    mediaInTweet();
    ~mediaInTweet();
};

#endif /* defined(__CppTwiLib__mediaInTweet__) */
