//
//  objects.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/08.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef __CppTwiLib__objects__
#define __CppTwiLib__objects__

#if defined _MSC_VER
#include <Windows.h>
#endif

#include <iostream>

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
    
#if defined _MSC_VER
    std::string UTF8toSjis(std::string srcUTF8){
        int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, NULL, 0);
        wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
        MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, bufUnicode, lenghtUnicode);
        
        int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
        char* bufShiftJis = new char[lengthSJis];
        WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);
        
        std::string strSJis(bufShiftJis);
        
        delete bufUnicode;
        delete bufShiftJis;
        
        return strSJis;
    }
    template<>
    bool getValuefromResponse<std::string>(std::string FieldName, std::string& distination){
        if (response.count(FieldName) == 0) {
            return false;
        }
        distination = UTF8toSjis( response[FieldName].get<std::string>() );
        return true;
    }
#endif /*_MSC_VER*/
    
};

#endif /* defined(__CppTwiLib__objects__) */
