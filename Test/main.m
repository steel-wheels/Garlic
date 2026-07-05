//
//  main.m
//  UnitTest
//
//  Created by Tomoo Hamada on 2026/07/05.
//

#import <Garlic/Garlic.h>
#import "UTList.h"

int main(int argc, const char * argv[])
{
        bool result = true ;

        result &= TestList() ;

        return result ? 0 : -1 ;
}
