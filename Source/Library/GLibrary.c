/**
 * @file        GLibrary.h
 * @brief       Define library functions
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#include "GLibrary.h"
#include "GList.h"
#include "GMemory.h"

void
GInitLibrary(void)
{
        GInitListPool() ;
        GInitMemory() ;

}
