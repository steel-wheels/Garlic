/**
 * @file        GString.h
 * @brief       Define GString data structure
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#ifndef GSTRING_H
#define GSTRING_H

#include <unistd.h>
#include <stdint.h>

#define G_STRING_UNIT_SIZE      64

struct GStringBody ;

struct GString {
        uint32_t                length ;
        struct GStringBody *    next ;
        char                    substring[4] ;
} ;

struct GStringBody {
        struct GStringBody *    next ;
        char                    substring[4] ;
} ;

static inline size_t
GSubstringLength(void)
{
        struct GString str = {0, NULL} ;
        const uint8_t * head   = (const uint8_t *) &str ;
        const uint8_t * substr = (const uint8_t *) &(str.substring[0]) ;
        return G_STRING_UNIT_SIZE - (substr - head) ;
}

static inline size_t
GSubstringBodyLength(void)
{
        struct GStringBody str = {NULL} ;
        const uint8_t * head   = (const uint8_t *)& str ;
        const uint8_t * substr = (const uint8_t *) &(str.substring[0]) ;
        return G_STRING_UNIT_SIZE - (substr - head) ;
}

struct GString *
GAllocateStringFromSource(const char * src) ;

void
GFreeString(struct GString * dst) ;

#endif /* GSTRING_H */
