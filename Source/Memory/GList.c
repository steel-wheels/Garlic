/**
 * @file        GList.c
 * @brief       Define GList data structure
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#include "GList.h"
#include <stdlib.h>

#define MAX_LIST_NUM            (128 - 1)

struct GListPool {
        struct GList           lists[MAX_LIST_NUM] ;
        struct GListPool *     next ;
} ;

static struct GListPool *      s_list_pool ;
static struct GList *          s_free_list ;

static inline struct GListPool *
allocateListPool(void)
{
        return malloc(sizeof(struct GListPool)) ;
}

static struct GList *
appendLists(struct GListPool * pool, struct GList * next)
{
        for(unsigned int i=0 ; i < MAX_LIST_NUM ; i++){
                (pool->lists[i]).data   = NULL ;
                (pool->lists[i]).next   = next ;
                next = &(pool->lists[i]) ;
        }
        return next ;
}

void
GInitListPool(void)
{
        s_list_pool = allocateListPool() ;
        s_list_pool->next = NULL ;
        s_free_list = appendLists(s_list_pool, NULL) ;
}

struct GList *
GAllocateList(void)
{
        if(s_free_list == NULL) {
                struct GListPool * newpool = allocateListPool() ;
                s_list_pool->next = newpool ;
                s_list_pool = newpool ;
                s_free_list = appendLists(newpool, NULL) ;
        }
        struct GList * result = s_free_list ;
        s_free_list = s_free_list->next ;
        return result ;
}

void
GFreeList(struct GList * src)
{
        src->data   = NULL ;
        src->next   = s_free_list ;
        s_free_list = src ;
}

uint64_t
GCountOfFreeLists(void)
{
        uint64_t        count = 0 ;
        struct GList *  list = s_free_list ;
        while(list->next != NULL){
                list = list->next ;
                count += 1 ;
        }
        return count ;
}
