/**
 * @file        GList.h
 * @brief       Define GList data structure
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#ifndef GLIST_H
#define GLIST_H

#include <stdbool.h>
#include <unistd.h>

struct GList {
        struct GList *          next ;
        void *                  data ;
} ;

void
GInitListPool(void) ;

struct GList *
GAllocateList(void) ;

void
GFreeList(struct GList * src) ;

uint64_t
GCountOfFreeLists(void) ;

#endif /* GLIST_H */
