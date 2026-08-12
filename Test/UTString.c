//
//  UTString.c
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/08/12.
//

#include "UTString.h"
#include <stdio.h>
#include <string.h>

bool
TestString(void)
{
        printf("* test string\n") ;

        bool result = true ;

        const char * src0 = "hello" ;

        struct GString * str0 ;

        str0 = GAllocateStringFromSource(src0) ;
        if(str0->length != strlen(src0)) {
                printf("[Error] Unvalid length\n") ;
                result = false ;
        }

        GFreeString(str0) ;
        return result ;
}

