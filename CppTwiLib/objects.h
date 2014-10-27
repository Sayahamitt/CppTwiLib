//
//  objects.h
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/08.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#ifndef __CppTwiLib__objects__
#define __CppTwiLib__objects__

#include <iostream>
#include "../picojson.h"

class Objects{
protected:
    picojson::object response;
    bool isempty;
public:
    Objects(picojson::object strip);
    Objects();
    Objects(const Objects& obj);
    virtual ~Objects();
    
    Objects& operator=(const Objects& rhs);
    
    void setJson(picojson::object);
    bool empty();

protected:
    template<typename TYPE>
    bool getValuefromResponse(std::string FieldName,TYPE& distination){
        if (response.count(FieldName) == 0) {
            return false;
        }
        distination = response[FieldName].get<TYPE>();
        return true;
    }
};

#endif /* defined(__CppTwiLib__objects__) */
