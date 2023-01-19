#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int al_init(arraylist_t *L, size_t length)
{
    L->data = malloc(sizeof(int) * length);
    if (!L->data) return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void al_destroy(arraylist_t *L)
{
    free(L->data);
}


int al_append(arraylist_t *L, int item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	int *p = realloc(L->data, sizeof(int) * size);
	if (!p) return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) printf("Increased size to %lu\n", size);
    }

    L->data[L->used] = item;
    ++L->used;

    return 0;
}


int al_remove(arraylist_t *L, int *item)
{
    if (L->used == 0) return 1;

    --L->used;

    if (item) *item = L->data[L->used];

    return 1;
}               
int al_insert(arraylist_t *list, int index, int item)
{
    if(!list || index < 0){
        return 1;
    }
    size_t length = list->length;
    if(index >= list->used){
        list-> used = index + 1;
    }
    else {
        list-> used += 1;
    }
    if(list->used > length && (list->used) <= (length*2)){
        list->data = realloc(list->data, sizeof(int)*(length*2));
        if(list->data == NULL){
            return 1;
        }
        list->length = length*2;
        length *= 2;
    }
    else if(list->used> length*2){
        list->data = realloc(list->data, sizeof(int)*(list->used));
        if(list->data == NULL){
            return 1;
        }
        list->length = list->used;
        length = list->used; 
    }
        for(int i = index+1; i < length; i++){
        list->data[i] = list->data[i-1];
    }
    list->data[index] = item;
    return 0;
}