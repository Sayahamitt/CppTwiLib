//
//  objects.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/08.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__objects__
#define __CppTwiLib__objects__

clude <iostream>

#include "macros.h"
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
    
    void setJson(const picojson::object& response);
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
   wiLib__objects__) */
