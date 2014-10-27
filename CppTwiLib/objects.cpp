//
//  objects.cpp
//  CppTwiLib
//
//  Created by Hiroki Yamasita on 2014/10/08.
//  Copyright (c) 2014年 Hiroki Yamasita. All rights reserved.
//

#include "objects.h"

Objects::Objects(picojson::object strip):response(strip){
    isempty=false;
}
Objects::Objects(){
    isempty=true;
}

Objects::Objects(const Objects& obj){
    this->response = obj.response;
    this->isempty = obj.isempty;
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