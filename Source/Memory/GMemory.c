/**
 * @file        GMemory.h
 * @brief       Define types for memory operation
 * @par Copyright
 *   Copyright (C) 2026 Steel Wheels Project
 */

#include "GMemory.h"
#include "GList.h"
#include <stdio.h>
#include <stdlib.h>

#define G_MEMORY_SLOT_NUM       512

static struct GList *          s_memory_slots[G_MEMORY_SLOT_NUM] ;
static struct GList *          s_memory_pages[G_MEMORY_SLOT_NUM] ;

static inline size_t
sizeToIndex(size_t size)
{
        size_t result = (size + G_UNIT_SIZE - 1) / G_UNIT_SIZE ;
        if(result >= G_MEMORY_SLOT_NUM) {
                fputs("[Error] Unexpected malloc size", stderr) ;
                exit(1) ;
        }
        return result ;
}

void
GInitMemory(void)
{
        for(unsigned int i=0 ; i < G_MEMORY_SLOT_NUM ; i++){
                s_memory_slots[i] = NULL ;
                s_memory_pages[i] = NULL ;
        }
}

static uint8_t *
allocatePage(size_t idx, size_t usize, unsigned int elmnum) ;

void *
GMalloc(size_t reqsize)
{
        size_t idx = sizeToIndex(reqsize) ;

        struct GList * list ;
        if((list = s_memory_slots[idx]) == NULL){
                static const unsigned int ELM_NUM = 128 ;

                /* allocate free slots */
                size_t usize = GSizeof(reqsize) ;
                uint8_t * head = allocatePage(idx, usize, ELM_NUM) ;
                for(unsigned int i=0 ; i < ELM_NUM ; i++){
                        uint8_t * data = head + (i * usize) ;
                        /* add new slot */
                        struct GList * newlist = GAllocateList() ;
                        newlist->data = data ;
                        newlist->next = s_memory_slots[idx] ;
                        s_memory_slots[idx] = newlist ;
                }
                list = s_memory_slots[idx] ;
        }
        /* return free slot */
        void * result = list->data ;
        s_memory_slots[idx] = list->next ;
        GFreeList(list) ;
        return result ;
}

static uint8_t *
allocatePage(size_t idx, size_t usize, unsigned int elmnum)
{
        uint8_t * data = malloc(usize * elmnum) ;

        struct GList * newlist = GAllocateList() ;
        newlist->data = data ;
        newlist->next = s_memory_pages[idx] ;
        s_memory_pages[idx] = newlist ;

        return data ;
}

void
GFree(size_t dstsize, void * dstptr)
{
        size_t idx = sizeToIndex(dstsize) ;

        struct GList * newlist = GAllocateList() ;
        newlist->data = dstptr ;
        newlist->next = s_memory_slots[idx] ;
        s_memory_slots[idx] = newlist ;
}

unsigned int
GCountOfFreeSlots(size_t reqsize)
{
        size_t idx = sizeToIndex(reqsize) ;
        const struct GList * list = s_memory_slots[idx] ;
        unsigned int result = 0 ;
        for( ; list != NULL ; list = list->next){
                result += 1 ;
        }
        return result ;
}
