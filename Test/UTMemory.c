//
//  UTMemory.c
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/07/12.
//

#include "UTMemory.h"
#include <stdio.h>

static bool
testMemory(size_t reqsize) ;

bool
TestMemory(void)
{
        printf("* test memory\n") ;
        bool result = true ;
        for(size_t usize=G_UNIT_SIZE ; usize < G_UNIT_SIZE * 32 ; usize += G_UNIT_SIZE) {
                result = testMemory(usize) ;
        }
        return result ;
}

static bool
testMemory(size_t reqsize)
{
        static const unsigned int ELM_NUM = 128 ;
        unsigned int count ;

        printf("* - req size: %lu\n", reqsize) ;

        bool result = true ;
        if((count = GCountOfFreeSlots(reqsize)) != 0){
                printf("[Error] Unexpected count (1): %u\n", count) ;
        }

        void * data[128] ;
        data[0] = GMalloc(reqsize) ;
        if((count = GCountOfFreeSlots(reqsize)) != ELM_NUM - 1){
                printf("[Error] Unexpected count (2): %u\n", count) ;
        }
        for(unsigned int i=1 ; i < ELM_NUM ; i++){
                data[i] = GMalloc(reqsize) ;
                if((count = GCountOfFreeSlots(reqsize)) != ELM_NUM - (i+1)){
                        printf("[Error] Unexpected count  (3): %u\n", count) ;
                }
        }
        for(unsigned int i=0 ; i < ELM_NUM ; i++){
                GFree(reqsize, data[i]) ;
                if((count = GCountOfFreeSlots(reqsize)) != i+1){
                        printf("[Error] Unexpected count  (4): %u\n", count) ;
                }
        }

        return result ;
}
