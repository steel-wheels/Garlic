/**
 * @file        GString.c
 * @brief       Define GString data structure
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#include "GString.h"
#include "GMemory.h"
#include <string.h>

static unsigned long
min(size_t a, size_t b)
{
        return a <= b ? a : b ;
}

static struct GStringBody *
GAllocateStringBodyFromSource(const char * src, size_t len)
{
        size_t bodylen = min(GSubstringBodyLength(), len) ;

        struct GStringBody * body = GMalloc(G_STRING_UNIT_SIZE) ;
        body->next = NULL ;
        memcpy(body->substring, src, bodylen) ;
        if(len > bodylen){
                struct GStringBody * next ;
                next = GAllocateStringBodyFromSource(src + bodylen, len - bodylen) ;
                body->next = next ;
        }
        return body ;
}

struct GString *
GAllocateStringFromSource(const char * src)
{
        size_t len = strlen(src) ;
        size_t headlen = min(GSubstringLength(), len) ;

        struct GString * head = GMalloc(G_STRING_UNIT_SIZE) ;
        head->length    = (uint32_t) len ;
        head->next      = NULL ;
        memcpy(head->substring, src, headlen) ;

        if(len > headlen) {
                struct GStringBody * body ;
                body = GAllocateStringBodyFromSource(src + headlen, len - headlen) ;
                head->next = body ;
        }

        return head ;
}

static void
GFreeStringBody(struct GStringBody * dst)
{
        struct GStringBody * next = dst->next ;
        if(next != NULL){
                GFreeStringBody(next) ;
        }
        GFree(G_STRING_UNIT_SIZE, dst) ;
}

void
GFreeString(struct GString * dst)
{
        struct GStringBody * next = dst->next ;
        if(next != NULL){
                GFreeStringBody(next) ;
        }
        GFree(G_STRING_UNIT_SIZE, dst) ;
}

