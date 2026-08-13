//
//  UTString.c
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/08/12.
//

#include "UTString.h"
#include <stdio.h>
#include <string.h>

static bool
test(const char * str1) ;

static const char *
make_string(char * dst, size_t length) ;

bool
TestString(void)
{
        printf("* test string\n") ;

        bool result = true ;
        char buf[512] ;

        result &= test("hello") ;
        result &= test("good morning everybpdy !!") ;
        result &= test(make_string(buf, 128)) ;
        result &= test(make_string(buf, 512)) ;

        return result ;
}

static const char *
make_string(char * dst, size_t length)
{
        for(size_t i=0 ; i<length ; i++){
                char c = 'a' + (i % 26) ;
                dst[i] = c ;
        }
        dst[length-1] = '\0' ;
        return dst ;
}

static bool
test(const char * str1)
{
        printf("test string: \"%s\"\n", str1) ;
        struct GString * str0 = GAllocateStringFromSource(str1) ;
        if(str0->length != strlen(str1)) {
                printf("[Error] Unvalid length\n") ;
                return false ;
        }
        if(GCompareStringWithNormal(str0, str1) == 0) {
                GFreeString(str0) ;
                return true ;
        } else {
                printf("[Error] Unexpected compariosn result\n") ;
                return false ;
        }
}
