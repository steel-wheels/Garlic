//
//  UTList.c
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/07/05.
//

#include "UTList.h"
#import <stdio.h>

#define MAX_LIST_NUM    (127 * 4)

static bool
checkCount(uint64_t count) ;

bool
TestList(void) {
        struct GList *  lists[MAX_LIST_NUM] ;
        bool result = true ;

        printf("* test list\n") ;

        uint64_t count = GCountOfFreeLists() ;

        /* allocate test */
        lists[0] = GAllocateList() ; count-- ;
        result &= checkCount(count) ;

        /* release test */
        GFreeList(lists[0]) ; lists[0] = NULL ; count++ ;
        result &= checkCount(count) ;

        /* allocate may list */
        for(unsigned int i=0 ; i < MAX_LIST_NUM ; i++) {
                lists[i] = GAllocateList() ;
        }
        count = 0 ;
        result &= checkCount(count) ;

        /* free may list */
        for(unsigned int i=0 ; i < MAX_LIST_NUM ; i++) {
                GFreeList(lists[i]) ;
                lists[i] = NULL ;
                count += 1 ;
        }
        result &= checkCount(count) ;

        return result ;
}

static bool
checkCount(uint64_t expcnt)
{
        uint64_t realcnt = GCountOfFreeLists() ;
        if(realcnt == expcnt){
                return true ;
        } else {
                fprintf(stderr, "[Error] Unexpected couunt: %llu <-> %llu\n", realcnt, expcnt) ;
                return false ;
        }
}
