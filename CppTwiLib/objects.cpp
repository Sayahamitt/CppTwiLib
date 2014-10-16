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
Objects::~Objects(){}

bool Objects::empty(){
    return isempty;
}