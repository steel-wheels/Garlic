//
//  main.m
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/07/05.
//

#import <Garlic/Garlic.h>
#import "UTList.h"
#import <stdio.h>

static void
init(void) ;

int main(int argc, const char * argv[])
{
        bool result = true ;

        init() ;
        result &= TestList() ;

        return result ? 0 : -1 ;
}

static void
init(void)
{
        GInitLibrary() ;
        uint64_t count = GCountOfFreeLists() ;
        printf("initial list pool count: %llu\n", count) ;
}
