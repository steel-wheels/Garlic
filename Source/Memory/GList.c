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
        struct GListPool * newpool = malloc(sizeof(struct GListPool)) ;
        newpool->next = NULL ;
        return newpool ;
}

static struct GList *
appendLists(struct GListPool * pool)
{
        struct GList * head = &(pool->lists[0]) ;
        struct GList * prev = head ;
        for(unsigned int i=1 ; i < MAX_LIST_NUM ; i++){
                struct GList * next = &(pool->lists[i]) ;
                next->data = NULL ;
                next->next = NULL ;
                prev->next = next ;
                prev = next ;
        }
        return head ;
}

void
GInitListPool(void)
{
        s_list_pool = allocateListPool() ;
        s_free_list = appendLists(s_list_pool) ;
}

struct GList *
GAllocateList(void)
{
        if(s_free_list == NULL) {
                struct GListPool * newpool = allocateListPool() ;
                s_list_pool->next = newpool ;
                s_list_pool = newpool ;
                s_free_list = appendLists(newpool) ;
        }
        struct GList * result = s_free_list ;
        s_free_list = s_free_list->next ;
        result->data = NULL ; result->next = NULL ;
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
        while(list != NULL){
                list = list->next ;
                count += 1 ;
        }
        return count ;
}
