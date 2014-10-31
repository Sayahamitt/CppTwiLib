//
//  macros.h
//  CppTwiLib
//
//  Created by Sayahamitt on 2014/10/31.
//  Copyright (c) 2014年 Sayahamitt. All rights reserved.
//

#ifndef CppTwiLib_macros_h
#define CppTwiLib_macros_h

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* gcc or VC10 */
#include <stdint.h>
#endif

#endif
