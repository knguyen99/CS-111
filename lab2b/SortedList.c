//Khoi Nguyen
//knguyen99@g.ucla.edu
//804993073
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
	if(list == NULL || element == NULL)
		return;
	SortedList_t* iter = list->next;
	while(iter != list && (strcmp(iter->key, element->key) <= 0))
	{
		iter = iter->next;
	}
	if(opt_yield & INSERT_YIELD)
		sched_yield();
	element->next = iter;
	element->prev = iter->prev;
	iter->prev->next = element;
	iter->prev = element;
}

int SortedList_delete( SortedListElement_t *element)
{
	if(element->next->prev != element || element->prev->next != element)
		return 1;
	if(opt_yield & DELETE_YIELD)
		sched_yield();
	element->next->prev = element->prev;
	element->prev->next = element->next;
	return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
	SortedListElement_t* iter = list->next;
	while(iter->key != NULL)
	{
		if(strcmp(iter->key, key) == 0)
			return iter;
		if(opt_yield & LOOKUP_YIELD)
			sched_yield();
		iter = iter->next;
	}
	return NULL;
}

int SortedList_length(SortedList_t *list)
{
	if(list == NULL)
		return -1;
        SortedList_t* iter = list->next;
        int c = 0;
        while(iter != list)
        {
		if(iter->next->prev != iter || iter->prev->next != iter)
			return -1;
		if(opt_yield & LOOKUP_YIELD)
			sched_yield();
		c++;
		iter = iter->next;	
        }
        return c;
}
