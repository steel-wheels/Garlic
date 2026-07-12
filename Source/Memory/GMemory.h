/**
 * @file        GList.h
 * @brief       Define types for memory operation
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#ifndef GMEMORY_H
#define GMEMORY_H

#include <unistd.h>

#define G_UNIT_SIZE             64

static inline size_t
GSizeof(size_t size)
{
        size_t tmp = (size + G_UNIT_SIZE - 1) / G_UNIT_SIZE ;
        return tmp * G_UNIT_SIZE ;
}

void
GInitMemory(void) ;

void *
GMalloc(size_t reqsize) ;

void
GFree(size_t dstsize, void * dstptr) ;

unsigned int
GCountOfFreeSlots(size_t reqsize) ;

#endif /* GMEMORY_H */
