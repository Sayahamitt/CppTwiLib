//
//  objects.cpp
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/08.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#include "objects.h"

Objects::Objects(picojson::object strip):
response(strip),
isempty(false){
}
Objects::Objects():
isempty(true){
}

Objects::Objects(const Objects& obj):
response(obj.response),
isempty(obj.isempty)
{
}

Objects& Objects::operator=(const Objects &rhs){
    this->response = rhs.response;
    this->isempty = rhs.isempty;
    return *this;
}

Objects::~Objects(){}

bool Objects::empty(){
    return isempty;
}

void Objects::setJson(const picojson::object& response){
    this->response = response;
}